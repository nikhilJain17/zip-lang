//
// Created by Nikhil Jain on 6/1/21.
//

#include "Codegen.h"

std::string Codegen::emitProgram(Node program) {
  // function decls

  // preamble -- in main function
  // statements
  // postamble
}

std::string Codegen::emitStatement(Node statement) {
  if (statement.getNodeType() == NodeType::LET_STATEMENT) {
    // store in currently scoped symbol table
    ScopedSymbolTable curr_scope = this->symbol_table_stack.top();
    std::optional<Node> symbol_opt = statement.getChild(NodeType::UNARY_IDENTIFIER);
    if (!symbol_opt.has_value()) error("No identifier in LET statement during codegen");

    std::string symbol_name = symbol_opt.value().getNodeData();
    SymTabEntry entry(symbol_name, SymbolType::INTVAR);

    // emit code to store variable on the stack
    std::optional<Node> immediate_opt = statement.getChild(NodeType::UNARY_CONST_INT);
    if (!immediate_opt.has_value()) error("No constant in LET statement during codegen");
    std::string immediate_str = immediate_opt.value().getNodeData();
    std::string code =
      "addi sp sp -4\n"                     // allocate space on the stack
      "addi t0 x0 " + immediate_str + "\n"   // put the immediate value into a temp register
      "sh t0 " + std::to_string(curr_scope.curr_fp_offset) + " sp";  // store in memory

    curr_scope.curr_fp_offset += 4;
    return code;
  }
  error("Invalid statement type in code generator");
}