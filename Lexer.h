//
// Created by Nikhil Jain on 6/1/21.
//

#ifndef ZIP_LANG_LEXER_H
#define ZIP_LANG_LEXER_H

#include <string>

enum TokenType {
  // Operators
  ADD,                  // '+'
  SUB,                  // '-'
  MUL,                  // '*'
  DIV,                  // '/'

  ASSIGN,               // '='

  // Comparators
  EQ,                   // '=='
  GT,                   // '>'
  GTE,                  // '>='
  LT,                   // '<'
  LTE,                  // '<='

  // Assignments
  IDENTIFIER,           // [a-zA-Z][a-zA-Z0-9]*
  INTEGER,              // [0-9]+

  // Misc
  ERROR

};

class Token {
private:
  TokenType type;
  std::string data;

public:
  Token(TokenType type, std::string data) {
    this->type = type;
    this->data = data;
  }

  TokenType getTokenType() { return this->type; }
  std::string getData() { return this->data; }
};

class Lexer {
private:
  std::string source;
  int curr_pos;
  char curr_char;
public:
  std::string getSource() { return this->source; }
  void getNextChar();
  Token getNextToken();
  char peek();
};


#endif //ZIP_LANG_LEXER_H
