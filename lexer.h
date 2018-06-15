#pragma once

#include <iostream>
#include <stdio.h>

class Token;

class Lexer
{
public:
  Lexer(std::istream& inputStream);
  ~Lexer();  
  
  Token* nextToken();
  Token* handleUnary(char c);
  int evalulateAlpha(std::string str);

  int m_line;
  int m_pos;
  std::string lexStr;
  char lastChar;  
  
private:
  char nextChar();
  std::istream& m_rinputStream;
};
