//
// Created by Nikhil Jain on 6/1/21.
//

#include "Lexer.h"

void Lexer::getNextChar() {
  if (curr_pos + 1 > this->source.size()) curr_char = '\0';
  curr_pos++;
  curr_char = source[curr_pos];
}

char Lexer::peek() {
  if (curr_pos + 1 > this->source.size()) return '\0';
  return source[curr_pos + 1];
}

// main lexer function
Token Lexer::getNextToken() {
  // match on operators
  if (curr_char == '+') return Token(ADD, "+");
  else if (curr_char == '-') return Token(SUB, "-");
  else if (curr_char == '*') return Token(MUL, "*");
  else if (curr_char == '/') return Token(DIV, "/");

  // match on comparators
  else if (curr_char == '=') {
    if (peek() == '=') return Token(EQ, "==");
    else return Token(ASSIGN, "=");
  }
  else if (curr_char == '>') {
    if (peek() == '=') return Token(GTE, ">=");
    else return Token(GT, ">");
  }
  else if (curr_char == '<') {
    if (peek() == '=') return Token(LTE, "<=");
    else return Token(LT, "<");
  }

  // identifiers etc
  else if (isdigit(curr_char)) {
    int start_index = curr_pos;
    while (isdigit(peek())) {
      getNextChar();
    }
    return Token(INTEGER, source.substr(start_index, curr_pos));
  }

  else {
    return Token(ERROR, "");
  }

}