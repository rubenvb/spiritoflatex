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
    namespace ascii = boost::spirit::x3::ascii;

    using x3::double_;
    using ascii::space;
    using x3::_attr;
    using x3::lit;
    using x3::char_;
    using x3::repeat;

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

    x3::rule<struct symbol, u8string> const symbol = "symbol";
    auto const symbol_def = '\\' >> (math_greek_upper_case_letter | math_greek_lower_case_letter);
    BOOST_SPIRIT_DEFINE(symbol)

    auto const element = symbol /*| command | underscore */ | char_;

    //auto const expression = element | ('{' > element > '}');

    x3::rule<struct tex_math, u8string> const tex_math = "tex_math";
    auto const tex_math_def = *(symbol | repeat(1)[char_]);
    BOOST_SPIRIT_DEFINE(tex_math)
  }
}
