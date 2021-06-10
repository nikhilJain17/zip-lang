//
// Created by Nikhil Jain on 6/1/21.
//

#include "Codegen.h"

std::string Codegen::emitProgram(Node program) {
  // preamble -- in main function
  // statements
  // postamble
}

std::string Codegen::emitStatement(Node statement) {
  if (statement.getNodeType() == NodeType::LET_STATEMENT) {
    // store in symbol table
    ScopedSymbolTable curr_scope = this->symbol_table_stack.top();
    std::optional<Node> symbol_opt = statement.getChild(NodeType::UNARY_IDENTIFIER);
    if (!symbol_opt.has_value()) error("No identifier in LET statement during codegen");

    std::string symbol_name = symbol_opt.value().getNodeData();
//    SymTabEntry entry(symbol_name, );

    // STOPSHIP: figure out what language features to build first

    // emit code to store variable on the stack
  }
  error("Invalid statement type in code generator");
}