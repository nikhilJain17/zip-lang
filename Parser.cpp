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
  while (curr_pos < tokens.size() && !checkTokenType(TokenType::ERROR, curr_token)
    && !checkTokenType(TokenType::ENDOFFILE, curr_token))
    program.addChild(parseStatement());
  return program;
}

Node Parser::parseStatement() {
  // Match on possible types of statements

  if (checkTokenType(TokenType::LET, curr_token)) {
    // "LET" <identifier> "=" <constant>
    Node let_stmt(NodeType::LET_STATEMENT);

    // Parse the remaining parts of the LET statement
    nextToken();
    Node identifier = parseIdentifier();
    if (!checkTokenType(TokenType::ASSIGN, curr_token)) error("Invalid LET statement, no '='");
    nextToken();
    Node constant = parseInteger();

    // Finish constructing the node
    let_stmt.addChild(identifier);
    let_stmt.addChild(constant);

    return let_stmt;
  }

  error("Invalid statement type!");
}

Node Parser::parseIdentifier() {
  if (!checkTokenType(TokenType::IDENTIFIER, curr_token))
    error("Expected identifier instead of token: " + curr_token.toString());

  Node identifier(NodeType::UNARY_IDENTIFIER, curr_token.getData());
  nextToken();
  return identifier;
}

Node Parser::parseInteger() {
  if (!checkTokenType(TokenType::INTEGER, curr_token))
    error("Expected integer constant instead of token: " + curr_token.toString());

  Node integer(NodeType::UNARY_CONST_INT, curr_token.getData());
  nextToken();
  return integer;
}

void error(std::string msg) {
  std::cout << msg << std::endl;
  exit(-1);
}