#include <iostream>
#include <cctype>
#include "lexer.h"
#include "token.h"

Lexer::Lexer(std::istream& inputStream) : m_rinputStream(inputStream)
{
  m_line = 1;
  m_pos = 1;
  lastChar = 0;
}

Lexer::~Lexer()
{
  
}

char Lexer::nextChar()
{
  char c = m_rinputStream.get();
  
  if (m_rinputStream.eof()) {
    return '$';
  }
  
  else if (c == '\n') {
    m_line++;
    m_pos = 1;
    return ' ';
  }
  
  else if (c == '#') {
    while (1) {
      char c2 = m_rinputStream.get();
      if (c2 == '\n') {
	m_line++;
	m_pos = 1;
	return ' ';
      }
    }
  }
  
  else {
    m_pos++;
    return c;
  }
}

Token* Lexer::handleUnary(char c)
{
  switch (c)
    {
    case '+':
      return new Token(Token::PLUS, "+", m_line, m_pos);
      break;
    case '-':
      return new Token(Token::MINUS, "-", m_line, m_pos);
      break;
    case '*':
      return new Token(Token::TIMES, "*", m_line, m_pos);
      break;
    case '/':
      return new Token(Token::DIVIDE, "/", m_line, m_pos);
      break;
    case '(':
      return new Token(Token::LPAREN, "(", m_line, m_pos);
      break;
    case ')':
      return new Token(Token::RPAREN, ")", m_line, m_pos);
      break;
    case '{':
      return new Token(Token::LBRACE, "{", m_line, m_pos);
      break;
    case '}':
      return new Token(Token::RBRACE, "}", m_line, m_pos);
      break;
    case ',':
      return new Token(Token::COMMA, ",", m_line, m_pos);
      break;
    case ';':
      return new Token(Token::SEMICOLON, ";", m_line, m_pos);
      break;
    default:
      return NULL;
    }
}

// Returns the correct token type for all isalpha()
int Lexer::evalulateAlpha(std::string str)
{
  if (str == "if") return Token::IF;
  else if (str == "else") return Token::ELSE;
  else if (str == "while") return Token::WHILE;
  else if (str == "function") return Token::FUNCTION;
  else if (str == "var") return Token::VAR;
  else if (str == "return") return Token::RETURN;
  else if (str == "printf") return Token::PRINTF;
  else return Token::IDENT;
}

Token* Lexer::nextToken()
{
  // OLD LEXER IMPL
  /*
    if (firstpass) {
    firstpass = !firstpass;
    if (lastToken)
    return lastToken;
    }
    
    char c = nextChar();
	
    if (c == ' ')
    return nextToken();
    
    if (c == '$')
    return new Token(Token::ENDOFFILE, "EOF", m_line, m_pos);
    
    if (c == 0x22) { // string literal
    while (1) {
    lexStr += c;
    
    if ((c = nextChar()) == 0x22) {
    lexStr += c;
    break;
    }
    }
    
    Token* tok = new Token(Token::STRINGLIT, lexStr, m_line, m_pos - lexStr.length());
    lexStr = "";
    return tok;
    }

    if (isalpha(c)) {
    while (1) {
    lexStr += c;
    c = nextChar();
    
    if (isspace(c))
    break;

    else if (ispunct(c)) {
    lastToken = new Token(getTokenType(c), std::string(1, c), m_line, m_pos - 1);
    firstpass = true;
    break;
    }
    }

    int tokenType = Token::IDENT;
    (lexStr == "if") ? tokenType = Token::IF : tokenType;
    (lexStr == "else") ? tokenType = Token::ELSE : tokenType;
    (lexStr == "while") ? tokenType = Token::WHILE : tokenType;
    (lexStr == "function") ? tokenType = Token::FUNCTION : tokenType;
    (lexStr == "var") ? tokenType = Token::VAR : tokenType;
    (lexStr == "return") ? tokenType = Token::RETURN : tokenType;
    (lexStr == "printf") ? tokenType = Token::PRINTF : tokenType;
    
    Token* tok = new Token(tokenType, lexStr, m_line, m_pos - lexStr.length() - 1);
    lexStr = "";
    return tok;
    }
    
    else if (isdigit(c)) {
    while (1) {
    if (!isspace(c))
    lexStr += c;
    c = nextChar();
    
    if (!isdigit(c) && ispunct(c)) {
    lastToken = new Token(getTokenType(c, nextChar()), std::string(1, c), m_line, m_pos - 1);
    firstpass = true;
    break;
    }
    }
    
    Token* tok = new Token(Token::INTLIT, lexStr, m_line, m_pos - lexStr.length() - 1);
    lexStr = "";
    return tok;
    }
    
    else if (ispunct(c)) {
    lexStr += c;
    if (c == '<' || c == '>' || c == '!' || c == '=') {
    char tmp = c;
    c = nextChar();
    if (getTokenType(tmp, c) == Token::GE || getTokenType(tmp, c) == Token::LE || getTokenType(tmp, c) == Token::NE)
    lexStr += c;
    }
    
    if (c == ')') {
    char tmp = c;
    c = nextChar();
    if (c == ';') {
    firstpass = true;
    lastToken = new Token(getTokenType(tmp), std::string(1, tmp), m_line, m_pos - 1);
    lexStr = "";
    return new Token(getTokenType(tmp), lexStr, m_line, m_pos - 1);
    }
    }
    
    Token* tok = new Token(getTokenType(lexStr.at(0), c), lexStr, m_line, m_pos - 1);
    lexStr = "";
    return tok;
    }
    
    return new Token(Token::ERROR, "Error", m_line, m_pos);
  */
  
  if (auto last = handleUnary(lastChar))
    {
      lastChar = 0;
      return last;
    }
  
  char c = nextChar();
  std::string str = "";
  
  while (isspace(c))
    {
      c = nextChar();
    }
  
  if (c == '$')
    return new Token(Token::ENDOFFILE, "EOF", m_line, m_pos);
  
  if (isalpha(c))
    {
      while (isalpha(c) || isdigit(c))
	{
	  str += c;
	  c = nextChar();
	}
      
      if (ispunct(c))
	lastChar = c;
      
      return new Token(evalulateAlpha(str), str, m_line, m_pos);
    }
  
  else if (isdigit(c))
    {
      while (isdigit(c))
	{
	  str += c;
	  c = nextChar();
	}
      
      if (ispunct(c))
	lastChar = c;
      
      return new Token(Token::INTLIT, str, m_line, m_pos);
    }
  
  else if (ispunct(c))
    {
      if (c == 0x22)
	{
	  c = nextChar();
	  while (c != 0x22)
	    {
	      str += c;
	      c = nextChar();
	    }
	  
	  return new Token(Token::STRINGLIT, str, m_line, m_pos);
	}
      
      if (Token* t = handleUnary(c)) // valid unary operator
	return t;
      
      else
	{
	  int type;
	  if (c == '=') {
	    lastChar = c;
	    c = nextChar();
	    (c == '=') ? type = Token::EQ : type = Token::ASSIGN;
	  }
	  
	  else if (c == '!') {
	    lastChar = c;
	    c = nextChar();
	    if (c == '=') type = Token::NE;
	  }
	  
	  else if (c == '<') {
	    lastChar = c;
	    c = nextChar();
	    if (c == '=') type = Token::LE;
	    else if (!ispunct(c)) type = Token::LT;
	  }
	  
	  else if (c == '>') {
	    lastChar = c;
	    c = nextChar();
	    if (c == '=') type = Token::GE;
	    else if (!ispunct(c)) type = Token::GT;
	  }
	  
	  else if (c == '&') {
	    lastChar = c;
	    c = nextChar();
	    if (c == '&') type = Token::AND;
	  }
	  
	  else if (c == '|') {
	    lastChar = c;
	    c = nextChar();
	    if (c == '|') type = Token::OR;
	  }
	  
	  return new Token(type, "", m_line, m_pos);
	}
      
    }
  
  else
    {
      return new Token(Token::ERROR, "ERROR", m_line, m_pos);
    }
}
