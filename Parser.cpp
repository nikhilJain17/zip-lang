//
// Created by Nikhil Jain on 6/1/21.
//

#include <iostream>
#include "Parser.h"

void Parser::nextToken() {
  if (curr_pos + 1 <= tokens.size()) {
    curr_pos++;
    curr_token = tokens[curr_pos];
  }
  else curr_token = Token(TokenType::ENDOFFILE, "\0");
}

Token Parser::peek() {
  if (curr_pos + 1 > tokens.size()) return Token(TokenType::ENDOFFILE, "\0");
  return tokens[curr_pos + 1];
}

Node Parser::parseProgram() {
  Node program(NodeType::PROGRAM);
  while (!tokens.empty())
    program.addChild(parseStatement());
  return program;
}

Node Parser::parseStatement() {
  // Match on possible types of statements
  if (checkTokenType(TokenType::LET, curr_token)) {
    // "LET" <identifier> "=" <constant>
    Node let_stmt(NodeType::LET_STATEMENT);

    nextToken();
    Node identifier = parseIdentifier();
    if (!checkTokenType(TokenType::ASSIGN, curr_token)) error("Invalid LET statement -- no '='");
    nextToken();
    Node constant = parseInteger();

    // STOPSHIP creating a LET_STATEMENT token...add the children

  }

  error("Invalid statement type!");
}

void error(std::string msg) {
  std::cout << msg << std::endl;
  exit(-1);
}