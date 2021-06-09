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

  // Comparators
  EQ,                   // '=='
  GT,                   // '>'
  GTE,                  // '>='
  LT,                   // '<'
  LTE,                  // '<='

  // Assignments
  IDENTIFIER,           // [a-zA-Z][a-zA-Z0-9]*
  INTEGER,              // [0-9]+
  LET,                  // "LET"
  ASSIGN,               // '='

  // Misc
  NEWLINE,
  ERROR,
  ENDOFFILE

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
  std::string toString() { return "IMPLEMENT ME!!!!!"; } // TODO implement lol
};

class Lexer {
private:
  std::string source;
  int curr_pos;
  char curr_char;
public:
  Lexer(std::string source) { this->source = source; this->curr_char = source[0]; this->curr_pos = 0; }
  std::string getSource() { return this->source; }
  void getNextChar();
  Token getNextToken();
  std::vector<Token> tokenize();
  char peek();
};


#endif //ZIP_LANG_LEXER_H
