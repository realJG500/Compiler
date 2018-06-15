#pragma once

#include <iostream>
#include <map>
#include <stack>
#include <vector>

class SymbolTable
{
public:
  SymbolTable();  
  ~SymbolTable();
  
  void enterScope();
  void exitScope();
  int addSymbol(std::string sym);
  int getUniqueSymbol(std::string sym);  
  
private:
  std::vector<std::map<int, std::string>> m_stack;
  
};

