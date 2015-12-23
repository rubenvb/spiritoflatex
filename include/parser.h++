/**
The MIT License (MIT)

Copyright (c) 2016 Ruben Van Boxem

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
**/

/*
 * parser
 * The full parser for all the (AMS)LaTeX math commands.
 */

#include "global.h++"
#include "u8string.h++"

#include <boost/spirit/home/x3.hpp>

#include <iterator>
#include <string>

namespace sol
{
  namespace parser
  {
    namespace x3 = boost::spirit::x3;

    using x3::double_;
    using x3::space;
    using x3::_attr;
    using x3::lit;
    using x3::char_;
    using x3::repeat;
    using x3::omit;
    using x3::alnum;

    extern const
    struct greek_lower_case_letters_ : x3::symbols<std::array<char,2>>
    {
        greek_lower_case_letters_();
    } greek_lower_case_letter;
    extern const
    struct greek_upper_case_letters_ : x3::symbols<std::array<char,2>>
    {
        greek_upper_case_letters_();
    } greek_upper_case_letter;

    extern const
    struct math_greek_lower_case_letters_ : x3::symbols<std::array<char,4>>
    {
        math_greek_lower_case_letters_();
    } math_greek_lower_case_letter;
    extern const
    struct math_greek_upper_case_letters_ : x3::symbols<std::array<char,4>>
    {
        math_greek_upper_case_letters_();
    } math_greek_upper_case_letter;

    extern const
    struct math_latin_lower_case_letters_ : x3::symbols<std::string>
    {
        math_latin_lower_case_letters_();
    } math_latin_lower_case_letter;
    extern const
    struct math_latin_upper_case_letters_ : x3::symbols<std::array<char,4>>
    {
        math_latin_upper_case_letters_();
    } math_latin_upper_case_letter;

    x3::rule<struct symbol, u8string> const named_letter = "named_letter";
    auto const named_letter_def = math_greek_upper_case_letter | math_greek_lower_case_letter;
    BOOST_SPIRIT_DEFINE(named_letter)

    x3::rule<struct ignored_math_command, u8string> const ignored_math_command = "ignored math command";
    auto const ignored_math_command_def = "label" >> -('{' >> (char_-'}') >> '}');
    BOOST_SPIRIT_DEFINE(ignored_math_command)

    x3::rule<struct math_command, u8string> const math_command = "math command";
    auto const math_command_def = '\\' >> (named_letter | ignored_math_command);// | ("label" -('{' > *omit[char_] > '}')));
    BOOST_SPIRIT_DEFINE(math_command)

    x3::rule<struct letter, u8string> const letter = "letter";
    auto const letter_def = math_latin_lower_case_letter | math_latin_upper_case_letter;
    BOOST_SPIRIT_DEFINE(letter)

    x3::rule<struct tex_math, u8string> const tex_math = "tex_math";
    auto const tex_math_def = *(math_command | letter);
    BOOST_SPIRIT_DEFINE(tex_math)

    x3::rule<struct inline_equation, u8string> const inline_equation = "inline equation";
    auto const inline_equation_def = '$' >> tex_math >> '$';
    BOOST_SPIRIT_DEFINE(inline_equation)

    x3::rule<struct display_equation, u8string> const display_equation = "display equation";
    auto const display_equation_def = lit("\\begin{equation}")
                                      >> tex_math
                                      >> lit("\\end{equation}");
    BOOST_SPIRIT_DEFINE(display_equation)

    x3::rule<struct document, u8string> const document = "document";
    auto const document_def = *(inline_equation | display_equation | omit[char_] );
    BOOST_SPIRIT_DEFINE(document)
  }
}
