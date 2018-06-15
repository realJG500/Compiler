#include "SymbolTable.h"
#include <cassert>
#include <cstring>

SymbolTable::SymbolTable()
{

}

SymbolTable::~SymbolTable()
{

}

/*
  Push a hastable on the stack
*/
void SymbolTable::enterScope()
{  
  std::map<int, std::string>* m = new std::map<int, std::string>;
  m_stack.push_back(*m);	
}

/*
  Pop the top hashtable off the stack
*/
void SymbolTable::exitScope()
{
  if (!m_stack.empty())
    m_stack.pop_back();
}

int SymbolTable::addSymbol(std::string sym)
{
  assert(m_stack.size() > 0);
  auto& hTable = m_stack.back();
  
  bool redefined = false;
  for (auto x = hTable.begin(); x != hTable.end(); ++x)
    {
      std::string str = x->second;
      if (str == sym)
	redefined = true;
    }
  
  if (!redefined) {
    hTable.insert(std::pair<int, std::string>(hTable.size() + 1, sym));
    return 1;
  }
  
  return 0;
}

int SymbolTable::getUniqueSymbol(std::string sym)
{
  for (int i = m_stack.size(); i > 0; i--)
    {
      auto stack = m_stack.at(i - 1);
      for (auto hTable = stack.begin(); hTable != stack.end(); ++hTable)
	{
	  if (hTable->second == sym)
	    return hTable->first;
	}
    }
  
  return 0;
}
