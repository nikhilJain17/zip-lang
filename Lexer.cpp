//
// Created by Nikhil Jain on 6/1/21.
//

#include <vector>
#include <iostream>
#include "Lexer.h"

// TODO rewrite some functions with streams / iterators...might be cleaner...
void Lexer::getNextChar() {
  if (curr_pos + 1 > this->source.size()) curr_char = '\0';
  curr_pos++;
  curr_char = source[curr_pos];
}

char Lexer::peek() {
  if (curr_pos + 1 > this->source.size()) return '\0';
  return source[curr_pos + 1];
}

// Tokenize the whole source
std::vector<Token> Lexer::tokenize() {

  std::vector<Token> tokens;

  while (peek() != '\0' && curr_pos < source.length()) {
    Token t = this->getNextToken();
    if (t.getTokenType() == TokenType::ERROR) {
      std::cout << "Invalid token: " << t.getData() << std::endl;
      exit(-1);
    }

    tokens.push_back(t);
  }
  return tokens;
}

// Lex the next token, consuming characters in the process.
Token Lexer::getNextToken() {
  // TODO get rid of whitespace or something
  while (isspace(curr_char)) getNextChar();

  // match on operators
  if (curr_char == '+') {
    this->getNextChar();
    return Token(ADD, "+");
  }
  else if (curr_char == '-') {
    this->getNextChar();
    return Token(SUB, "-");
  }
  else if (curr_char == '*') {
    this->getNextChar();
    return Token(MUL, "*");
  }
  else if (curr_char == '/') {
    this->getNextChar();
    return Token(DIV, "/");
  }
  else if (curr_char == '\n') {
    this->getNextChar();
    return Token(NEWLINE, "\n");
  }
  else if (curr_char == '=') {
    this->getNextChar();
    return Token(ASSIGN, "=");
  }

  // match on comparators
  else if (curr_char == '=') {
    this->getNextChar();
    if (curr_char == '=') {
      this->getNextChar();
      return Token(EQ, "==");
    }
    else return Token(ASSIGN, "=");
  }
  else if (curr_char == '>') {
    this->getNextChar();
    if (curr_char == '=') {
      this->getNextChar();
      return Token(GTE, ">=");
    }
    else return Token(GT, ">");
  }
  else if (curr_char == '<') {
    this->getNextChar();
    if (peek() == '=') {
      this->getNextChar();
      return Token(LTE, "<=");
    }
    else return Token(LT, "<");
  }

  // TODO make a function to check for keywords
  // "LET"
  else if (curr_char == 'L') {
    if (curr_pos + 2 < source.length()) {
      if (source[curr_pos + 1] == 'E' && source[curr_pos + 2] == 'T') {
        this->getNextChar();
        this->getNextChar();
        this->getNextChar();
        return Token(LET, "LET");
      }
    } // TODO handle case for identifiers starting with LE !!!
  }

  // integers
  else if (isdigit(curr_char)) {
    int start_index = curr_pos;
    getNextChar();
    while (isdigit(curr_char) && curr_char != '\0') {
      getNextChar();
    }
    return Token(INTEGER, source.substr(start_index, curr_pos - start_index));
  }

  // identifiers
  else if (isalpha(curr_char)) {
    int start_index = curr_pos;
    getNextChar();
    while ((isdigit(curr_char) || isalpha(curr_char)) && !isspace(curr_char) && curr_char != '\0') {
      getNextChar();
    }
    return Token(IDENTIFIER, source.substr(start_index, curr_pos - start_index));
  }

  return Token(ERROR, "todo put something here maybe");
}