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
  // TODO get rid of whitespace or something

  // match on operators
  if (curr_char == '+') return Token(ADD, "+");
  else if (curr_char == '-') return Token(SUB, "-");
  else if (curr_char == '*') return Token(MUL, "*");
  else if (curr_char == '/') return Token(DIV, "/");
  else if (curr_char == '\n') return Token(NEWLINE, "\n");
  else if (curr_char == '=') return Token(ASSIGN, "=");

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

  // TODO make a function to check for keywords
  // "LET"
  else if (curr_char == 'L') {
    if (curr_char + 2 < source.length()) {
      if (source[curr_pos + 1] == 'E' && source[curr_pos + 2] == 'T') {
        return Token(LET, "LET");
      }
    }
  }

  // integers
  else if (isdigit(curr_char)) {
    int start_index = curr_pos;
    while (isdigit(peek())) {
      getNextChar();
    }
    return Token(INTEGER, source.substr(start_index, curr_pos));
  }

  // identifiers
  else if (isalpha(curr_char)) {
    int start_index = curr_pos;
    while (isdigit(peek()) || isalpha(peek())) {
      getNextChar();
    }
    return Token(IDENTIFIER, source.substr(start_index, curr_pos));
  }

  else return Token(ERROR, "");
}