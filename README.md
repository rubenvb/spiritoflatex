# spiritoflatex

Boost.Spirit parser for (AMS)LaTeX Mathematics.

It uses Boost Spirit X3 to transform (AMS)LaTeX commands into various representations:
 - inline Unicode (as defined in [Unicode Technical note 28](http://unicode.org/notes/tn28/UTN28-PlainTextMath-v3.pdf))
 - an AST, ready to manipulate in the sense of a Computer Algebra System and numerical calculator
 - HTML, such that it can be rendered everywhere, including Qt's GUI, resulting in a WYSIWYG editor,
 - PDF, once more document-related commands and or settings are included,
 - ...

Currently an academic project to teach myself Boost.Spirit, and hopefully will lead to a useful
program.
