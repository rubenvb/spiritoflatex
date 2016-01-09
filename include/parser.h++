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
    using x3::rule;
    using x3::symbols;
    using x3::char_;
    using x3::lit;
    using x3::omit;
    using x3::lexeme;
    using x3::space;
    using x3::alnum;
    using x3::repeat;

    extern const
    struct greek_lower_case_letters_ : symbols<std::array<char,2>>
    {
        greek_lower_case_letters_();
    } greek_lower_case_letter;
    extern const
    struct greek_upper_case_letters_ : symbols<std::array<char,2>>
    {
        greek_upper_case_letters_();
    } greek_upper_case_letter;

    extern const
    struct math_greek_lower_case_letters_ : symbols<std::array<char,4>>
    {
        math_greek_lower_case_letters_();
    } math_greek_lower_case_letter;
    extern const
    struct math_greek_upper_case_letters_ : symbols<std::array<char,4>>
    {
        math_greek_upper_case_letters_();
    } math_greek_upper_case_letter;

    extern const
    struct math_latin_lower_case_letters_ : symbols<std::string>
    {
        math_latin_lower_case_letters_();
    } math_latin_lower_case_letter;
    extern const
    struct math_latin_upper_case_letters_ : symbols<std::array<char,4>>
    {
        math_latin_upper_case_letters_();
    } math_latin_upper_case_letter;
    extern const
    struct math_miscellaneous_letters_ : symbols<std::string>
    {
      math_miscellaneous_letters_();
    } math_miscellaneous_letter;

    rule<struct document,             u8string> const document             = "document";
    rule<struct text,                 u8string> const text                 = "text";
    rule<struct token,                u8string> const token                = "token";
    rule<struct letter,               u8string> const letter               = "letter";
    rule<struct math_command,         u8string> const math_command         = "math command";
    rule<struct named_letter,         u8string> const named_letter         = "named letter";
    rule<struct ignored_math_command, u8string> const ignored_math_command = "math command (ignored)";
    rule<struct ignored_label,        u8string> const ignored_label        = "label (ignored)";
    rule<struct superscript,          u8string> const superscript          = "superscript";
    rule<struct subscript,            u8string> const subscript            = "subscript";
    rule<struct group,                u8string> const group                = "group";
    rule<struct tex_math,             u8string> const tex_math             = "TeX math";
    rule<struct inline_equation,      u8string> const inline_equation      = "inline equation";
    rule<struct display_equation,     u8string> const display_equation     = "display equation";

    /*
     * all rules, top-down
     */
    // document: ignore all non-equation stuff for now
    auto const document_def = *(inline_equation | display_equation | text);
    // text part of the document
    auto const text_def = lexeme[repeat(1)[alnum]];
    // single symbol/construct in an equation
    auto const token_def = lexeme [ letter | math_command ];
    // latin letters mapped to unicode math italic version
    auto const letter_def = math_latin_lower_case_letter | math_latin_upper_case_letter;
    // LaTeX math commands, including other letters and other symbols
    auto const math_command_def = '\\' >> (named_letter | ignored_math_command);
    // other letters
    auto const named_letter_def = math_greek_upper_case_letter | math_greek_lower_case_letter
                                  | math_miscellaneous_letter;
    // math commands currently not implemented
    auto const ignored_math_command_def = ignored_label
                                          | "bm" | "left" | "right"
                                          | (lit("frac") >> '{' >> tex_math >> "}{" >> tex_math >> '}');
    // ignore label followed by key
    auto const ignored_label_def = lit("label") >> '{' >> *(omit[char_]-'}') >> '}';

    auto const superscript_def = '^' >> group;

    auto const subscript_def = '_' >> group;

    auto const group_def = ('{' >> group >> '}') | token >> *(superscript | subscript) >> *group;

    auto const tex_math_def = *group;

    auto const inline_equation_def = '$' >> tex_math >> '$';

    auto const display_equation_def = lit("\\begin{equation}")
                                      >> tex_math
                                      >> lit("\\end{equation}");

    BOOST_SPIRIT_DEFINE(document)
    BOOST_SPIRIT_DEFINE(text)
    BOOST_SPIRIT_DEFINE(token)
    BOOST_SPIRIT_DEFINE(letter)
    BOOST_SPIRIT_DEFINE(math_command)
    BOOST_SPIRIT_DEFINE(named_letter)
    BOOST_SPIRIT_DEFINE(ignored_math_command)
    BOOST_SPIRIT_DEFINE(ignored_label)
    BOOST_SPIRIT_DEFINE(superscript)
    BOOST_SPIRIT_DEFINE(subscript)
    BOOST_SPIRIT_DEFINE(group)
    BOOST_SPIRIT_DEFINE(tex_math)
    BOOST_SPIRIT_DEFINE(inline_equation)
    BOOST_SPIRIT_DEFINE(display_equation)
  }
}
