//
// Created by Nikhil Jain on 6/1/21.
//

#ifndef ZIP_LANG_CODEGEN_H
#define ZIP_LANG_CODEGEN_H

#include <stack>
#include "Parser.h"

enum SymbolType {
  // TODO think about what types are allowed...
  INT,
  FLOAT,
  STRING,
  BOOL,
  FUNC
};

class SymTabEntry {
public: // TODO make these private and do getters/setters
  std::string symbol_name;
  SymbolType type;

  SymTabEntry(std::string symbol_name, SymbolType type) {
    this->type = type;
    this->symbol_name = symbol_name;
  }

};

// A symbol table storing variables only for a particular scope
class ScopedSymbolTable {
private:
public:
  std::map<std::string, SymTabEntry> scoped_sym_tab;
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
