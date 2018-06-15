#include "token.h"

Token::Token()
{
  
}

Token::Token(int type, std::string lexeme, int line, int pos)
{
  m_ttype = type;
  m_lexeme = lexeme;
  m_line = line;
  m_pos = pos;
}

Token::~Token()
{
  
}

int Token::type()
{
  return m_ttype;
}

std::string Token::lexeme()
{
  return m_lexeme;
}

int Token::line()
{
  return m_line;
}

int Token::pos()
{
  return m_pos;
}
