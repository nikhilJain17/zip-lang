//
// Created by Nikhil Jain on 6/1/21.
//

#ifndef ZIP_LANG_CODEGEN_H
#define ZIP_LANG_CODEGEN_H

#include <stack>
#include <utility>
#include "Parser.h"

enum SymbolType {
  // TODO think about what types are allowed...
  INTVAR,
  STRINGVAR,
  FUNC
};

class SymTabEntry {
public: // TODO make these private and do getters/setters
  std::string symbol_name;
  SymbolType type;
  int fp_offset;                  // offset from stack's frame pointer

  SymTabEntry(std::string symbol_name, SymbolType type) {
    this->type = type;
    this->symbol_name = std::move(symbol_name);
  }

};

// A symbol table storing variables only for a particular scope
class ScopedSymbolTable {
private:
public:
  int curr_fp_offset;           // how much have we already allocated in this stack frame...todo can we just do SP - FP?
  std::map<std::string, SymTabEntry> scoped_sym_tab;
  ScopedSymbolTable() {
    curr_fp_offset = 0;
  }
};

class Codegen {
private:
  Node root;
  std::stack<ScopedSymbolTable> symbol_table_stack;
  // TODO add symbol table (with scope?), func decl table
public:
  Codegen(Node root1) : root(root1) {
    ScopedSymbolTable global_scope{};
    symbol_table_stack.push(global_scope);
  }
  std::string emitProgram(Node);
  std::string emitStatement(Node);
};


#endif //ZIP_LANG_CODEGEN_H
