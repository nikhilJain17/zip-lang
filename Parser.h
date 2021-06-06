//
// Created by Nikhil Jain on 6/1/21.
//

#ifndef ZIP_LANG_PARSER_H
#define ZIP_LANG_PARSER_H

#include <vector>
#include "string"
#include "Lexer.h"

// AST node types
enum NodeType {
  PROGRAM,
  LET_STATEMENT,
  COMPARISON,
  EXPRESSION,
  TERM,
  UNARY_CONST_INT,
  UNARY_IDENTIFIER
};

class Node {
private:
  NodeType type;
  std::string data;           // TODO make this a byte? will need to add more "data" fields later.
  std::vector<Node> children; // TODO vector?

public:
  explicit Node(NodeType type) { this->type = type; }
  NodeType getNodeType() { return type; }
  void addChild(Node child) { this->children.push_back(child); }
};

class Parser {
private:
  std::vector<Token> tokens;
  int curr_pos;
  Token curr_token;

  void nextToken();
  Token peek();

  bool checkTokenType(TokenType expectedType, Token actual) { return expectedType == actual.getTokenType(); }

  Node parseStatement();
  Node parseExpression();
  Node parseTerm();
  Node parseUnary();
  Node parseInteger();
  Node parseIdentifier();
public:
  Node parseProgram();

};

void error(std::string);

#endif //ZIP_LANG_PARSER_H
