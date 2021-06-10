//
// Created by Nikhil Jain on 6/1/21.
//

#ifndef ZIP_LANG_PARSER_H
#define ZIP_LANG_PARSER_H

#include <vector>
#include <map>
#include "string"
#include "Lexer.h"

void error(std::string);

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

//// TODO have a NodeType::toString function or something
//std::string nodeTypeToString(NodeType t);

class Node {
private:
  NodeType type;
  std::string data;                  // TODO make this a byte? will need to add more "data" fields later.
  std::map<NodeType, Node> children; // TODO put string key in constant file

public:
  explicit Node(NodeType type, std::string data = "") { this->type = type; this->data = data; }
  NodeType getNodeType() { return type; }
  std::string getNodeData() { return data; }
  std::string toString() { return "(" /* + nodeTypeToString(this->type) + ", " */ + this->data + ")"; }
  void addChild(Node child) {
    if (this->children.count(child.getNodeType()) > 0) error("Duplicate child: " + child.toString() + " of: " + this->toString());
    this->children.insert((std::pair(child.getNodeType(), child)));
  }
  std::optional<Node> getChild(NodeType type) {
    if (children.count(type) > 0) return children.at(type);
    return std::nullopt;
  }
};

class Parser {
private:
  std::vector<Token> tokens;
  int curr_pos;
  Token curr_token;
  Token peek();

  void nextToken();
  bool checkTokenType(TokenType expectedType, Token actual) { return expectedType == actual.getTokenType(); }

  Node parseStatement();
  Node parseExpression();
  Node parseTerm();
  Node parseUnary();
  Node parseInteger();
  Node parseIdentifier();
public:
  Parser(std::vector<Token> tokens) : curr_token(tokens.at(0)) { this->tokens = tokens; }
  Node parseProgram();
  std::string printAST() { return "IMPLEMENT ME!!"; } // TODO implement me

};

#endif //ZIP_LANG_PARSER_H
