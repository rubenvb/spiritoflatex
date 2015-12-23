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

#include "gui.h++"

#include <iomanip>
#include <boost/lexical_cast.hpp>

#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "parser.h++"

gui::gui(QWidget* parent)
: QWidget(parent),
  input(new QTextEdit(this)),
  output(new QLabel(this)),
  parse_button(new QPushButton("Parse!", this))
{
  auto layout = new QVBoxLayout();
  auto toplayout = new QHBoxLayout();
  toplayout->addWidget(input);
  toplayout->addWidget(parse_button);
  layout->addLayout(toplayout);
  layout->addWidget(output);
  this->setLayout(layout);

  connect(parse_button, &QPushButton::clicked,
          this, &gui::parse_input);
}

void gui::parse_input()
{
  using namespace sol::parser;
  static auto const symbol = '\\' >> (math_greek_upper_case_letter | math_greek_lower_case_letter);
  static auto const tex_math = *(symbol | repeat(1)[char_]);

  QByteArray input_data = input->toPlainText().toUtf8();
  const u8string input_string(input_data.constData(), input_data.constData()+input_data.size());
  u8string result;
  qDebug() << input_string.data();
  auto first = input_string.begin();
  auto last = input_string.end();
  bool success = x3::phrase_parse(first, last,
                              // Begin grammar
                              document//tex_math
                              ,
                              // End grammar
                              space,
                              result);
  if(first != last)
    output->setText("Parsing partially succeeded: "
                    + QString::fromUtf8(result.data(), static_cast<int>(result.size())));
  else if(!success)
    output->setText("Parsing failed.");
  else
  {
    assert(first == last);
    assert(success);
    qDebug() << result.size() << ": ";
    for(char c : result)
      qDebug() << QByteArray(1,c).toHex();

    output->setText("Parsing succeeded: "
                    + QString::fromUtf8(result.data(), static_cast<int>(result.size())));
  }
}
