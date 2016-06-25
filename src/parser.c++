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

#include "parser.h++"

namespace sol
{
  namespace parser
  {
    const greek_lower_case_letters_ greek_lower_case_letter;
    greek_lower_case_letters_::greek_lower_case_letters_()
    {
      add
          ("textalpha",   u8"\u03B1"_u8char2)
          ("textbeta",    u8"\u03B2"_u8char2)
          ("textgamma",   u8"\u03B3"_u8char2)
          ("textdelta",   u8"\u03B4"_u8char2)
          ("textepsilon", u8"\u03B5"_u8char2)
          ("textzeta",    u8"\u03B6"_u8char2)
          ("texteta",     u8"\u03B7"_u8char2)
          ("texttheta",   u8"\u03B8"_u8char2)
          ("textiota",    u8"\u03B9"_u8char2)
          ("textkappa",   u8"\u03BA"_u8char2)
          ("textlambda",  u8"\u03BB"_u8char2)
          ("textmu",      u8"\u03BC"_u8char2)
          ("textnu",      u8"\u03BD"_u8char2)
          ("textxi",      u8"\u03BE"_u8char2)
          ("textomicron", u8"\u03BF"_u8char2)
          ("textpi",      u8"\u03C0"_u8char2)
          ("textrho",     u8"\u03C1"_u8char2)
          ("textsigma",   u8"\u03C3"_u8char2) // U+03C2 is varsigma
          ("texttau",     u8"\u03C4"_u8char2)
          ("textupsilon", u8"\u03C5"_u8char2)
          ("textphi",     u8"\u03D5"_u8char2) // U+03C4 is varphi
          ("textchi",     u8"\u03C7"_u8char2)
          ("textpsi",     u8"\u03C8"_u8char2)
          ("textomega",   u8"\u03C9"_u8char2)
      ;
    }
    const greek_upper_case_letters_ greek_upper_case_letter;
    greek_upper_case_letters_::greek_upper_case_letters_()
    {
      add
          ("textAlpha",   u8"\u0391"_u8char2)
          ("textBeta",    u8"\u0392"_u8char2)
          ("textGamma",   u8"\u0393"_u8char2)
          ("textDelta",   u8"\u0394"_u8char2)
          ("textEpsilon", u8"\u0395"_u8char2)
          ("textZeta",    u8"\u0396"_u8char2)
          ("textEta",     u8"\u0397"_u8char2)
          ("textTheta",   u8"\u0398"_u8char2)
          ("textIota",    u8"\u0399"_u8char2)
          ("textKappa",   u8"\u039A"_u8char2)
          ("textLambda",  u8"\u039B"_u8char2)
          ("textMu",      u8"\u039C"_u8char2)
          ("textNu",      u8"\u039D"_u8char2)
          ("textXi",      u8"\u039E"_u8char2)
          ("textOmicron", u8"\u039F"_u8char2)
          ("textPi",      u8"\u03A0"_u8char2)
          ("textRho",     u8"\u03A1"_u8char2)
          ("textSigma",   u8"\u03A3"_u8char2) // U+03A2 is unassigned
          ("textTau",     u8"\u03A4"_u8char2)
          ("textUpsilon", u8"\u03A5"_u8char2)
          ("textPhi",     u8"\u03A6"_u8char2)
          ("textChi",     u8"\u03A7"_u8char2)
          ("textPsi",     u8"\u03A8"_u8char2)
          ("textOmega",   u8"\u03C9"_u8char2)
      ;
    }

//#ifdef SPIRITOFLATEX_USE_UNICODE_MATHEMATICAL_ALPHANUMERIC_SYMBOLS
    const math_greek_lower_case_letters_ math_greek_lower_case_letter;
    math_greek_lower_case_letters_::math_greek_lower_case_letters_()
    {
      add
          ("alpha",   u8"\U0001D6FC"_u8char4)
          ("beta",    u8"\U0001D6FD"_u8char4)
          ("gamma",   u8"\U0001D6FE"_u8char4)
          ("delta",   u8"\U0001D6FF"_u8char4)
          ("epsilon", u8"\U000003F5"_u8char4)
          ("zeta",    u8"\U0001D701"_u8char4)
          ("eta",     u8"\U0001D702"_u8char4)
          ("theta",   u8"\U0001D703"_u8char4)
          ("iota",    u8"\U0001D704"_u8char4)
          ("kappa",   u8"\U0001D705"_u8char4)
          ("lambda",  u8"\U0001D706"_u8char4)
          ("mu",      u8"\U0001D707"_u8char4)
          ("nu",      u8"\U0001D708"_u8char4)
          ("xi",      u8"\U0001D709"_u8char4)
          ("omicron", u8"\U0001D70A"_u8char4)
          ("pi",      u8"\U0001D70B"_u8char4)
          ("rho",     u8"\U0001D70C"_u8char4)
          ("sigma",   u8"\U0001D70E"_u8char4)
          ("tau",     u8"\U0001D70F"_u8char4)
          ("upsilon", u8"\U0001D710"_u8char4)
          ("phi",     u8"\U0001D711"_u8char4)
          ("chi",     u8"\U0001D712"_u8char4)
          ("psi",     u8"\U0001D713"_u8char4)
          ("omega",   u8"\U0001D714"_u8char4)
      ;
    }
    const math_greek_upper_case_letters_ math_greek_upper_case_letter;
    math_greek_upper_case_letters_::math_greek_upper_case_letters_()
    {
      add
          ("Alpha",   u8"\U0001D6E2"_u8char4)
          ("Beta",    u8"\U0001D6E3"_u8char4)
          ("Gamma",   u8"\U0001D6E4"_u8char4)
          ("Delta",   u8"\U0001D6E5"_u8char4)
          ("Epsilon", u8"\U0001D6E6"_u8char4)
          ("Zeta",    u8"\U0001D6E7"_u8char4)
          ("Eta",     u8"\U0001D6E8"_u8char4)
          ("Theta",   u8"\U0001D6E9"_u8char4)
          ("Iota",    u8"\U0001D6EA"_u8char4)
          ("Kappa",   u8"\U0001D6EB"_u8char4)
          ("Lambda",  u8"\U0001D6EC"_u8char4)
          ("Mu",      u8"\U0001D6ED"_u8char4)
          ("Nu",      u8"\U0001D6EE"_u8char4)
          ("Xi",      u8"\U0001D6EF"_u8char4)
          ("Omicron", u8"\U0001D6F0"_u8char4)
          ("Pi",      u8"\U0001D6F1"_u8char4)
          ("Rho",     u8"\U0001D6F2"_u8char4)
          ("Theta",   u8"\U0001D6F3"_u8char4)
          ("Sigma",   u8"\U0001D6F4"_u8char4)
          ("Tau",     u8"\U0001D6F5"_u8char4)
          ("Upsilon", u8"\U0001D6F6"_u8char4)
          ("Phi",     u8"\U0001D6F7"_u8char4)
          ("Chi",     u8"\U0001D6F8"_u8char4)
          ("Psi",     u8"\U0001D6F9"_u8char4)
          ("Omega",   u8"\U0001D6FA"_u8char4)
      ;
    }

    const math_latin_lower_case_letters_ math_latin_lower_case_letter;
    math_latin_lower_case_letters_::math_latin_lower_case_letters_()
    {
      add
          ("a", u8"\U0001D44E")
          ("b", u8"\U0001D44F")
          ("c", u8"\U0001D450")
          ("d", u8"\U0001D451")
          ("e", u8"\U0001D452")
          ("f", u8"\U0001D453")
          ("g", u8"\U0001D454")
          ("h", u8"\U0000210E") // this one is one byte shorter than the rest
          ("i", u8"\U0001D456")
          ("j", u8"\U0001D457")
          ("k", u8"\U0001D458")
          ("l", u8"\U0001D459")
          ("m", u8"\U0001D45A")
          ("n", u8"\U0001D45B")
          ("o", u8"\U0001D45C")
          ("p", u8"\U0001D45D")
          ("q", u8"\U0001D45E")
          ("r", u8"\U0001D45F")
          ("s", u8"\U0001D460")
          ("t", u8"\U0001D461")
          ("u", u8"\U0001D462")
          ("v", u8"\U0001D463")
          ("w", u8"\U0001D464")
          ("x", u8"\U0001D465")
          ("y", u8"\U0001D466")
          ("z", u8"\U0001D467")
       ;
    }
    const math_latin_upper_case_letters_ math_latin_upper_case_letter;
    math_latin_upper_case_letters_::math_latin_upper_case_letters_()
    {
      add
          ("A", u8"\U0001D434"_u8char4)
          ("B", u8"\U0001D435"_u8char4)
          ("C", u8"\U0001D436"_u8char4)
          ("D", u8"\U0001D437"_u8char4)
          ("E", u8"\U0001D438"_u8char4)
          ("F", u8"\U0001D439"_u8char4)
          ("G", u8"\U0001D43A"_u8char4)
          ("H", u8"\U0001D43B"_u8char4)
          ("I", u8"\U0001D43C"_u8char4)
          ("J", u8"\U0001D43D"_u8char4)
          ("K", u8"\U0001D43E"_u8char4)
          ("L", u8"\U0001D43F"_u8char4)
          ("M", u8"\U0001D440"_u8char4)
          ("N", u8"\U0001D441"_u8char4)
          ("O", u8"\U0001D442"_u8char4)
          ("p", u8"\U0001D443"_u8char4)
          ("Q", u8"\U0001D444"_u8char4)
          ("R", u8"\U0001D445"_u8char4)
          ("S", u8"\U0001D446"_u8char4)
          ("T", u8"\U0001D447"_u8char4)
          ("U", u8"\U0001D448"_u8char4)
          ("V", u8"\U0001D449"_u8char4)
          ("W", u8"\U0001D44A"_u8char4)
          ("X", u8"\U0001D44B"_u8char4)
          ("Y", u8"\U0001D44C"_u8char4)
          ("Z", u8"\U0001D44D"_u8char4)
       ;
    }
    const math_miscellaneous_letters_ math_miscellaneous_letter;
    math_miscellaneous_letters_::math_miscellaneous_letters_()
    {
      add
          ("varepsilon", u8"\U0001D700")
         ;
    }
//#else
//    const greek_lower_case_letters_ math_greek_lower_case_letter = greek_lower_case_letter;
//    const greek_upper_case_letters_ math_greek_upper_case_letter = greek_upper_case_letter;

//#endif
  }
}
