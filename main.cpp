//
// Created by Nikhil Jain on 5/31/21.
//


#include <iostream>
#include "Parser.h"
//#include "Lexer.h"

int main() {
  std::cout << "Hello world\n";

  // Lex
  std::string program = "LET xyz = 10";
  Lexer lexer(program);
  std::vector<Token> tokens = lexer.tokenize();

  // Parse
  Parser parser(tokens);
  Node root = parser.parseProgram();


}