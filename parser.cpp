// Compile with '-std=c++0x' ;; required for various c++11 features

#include "parser.h"

const std::string Parser::ops[] = { "ADD", "SUB", "MULT", "DIV",
				    "ISEQ", "ISNE", "ISLT", "ISLE", "ISGT", "ISGE",
				    "AND", "OR",
				    "LOADL", "LOADV", "STORE",
				    "JUMP", "JUMPF", "JUMPT", "CALL", "RET",
				    "PRINTF",
				    "LABEL", "SEQ" };


Parser::Parser(Lexer& lexerx, std::ostream& outx) : lexer(lexerx), out(outx), lindex(1), tindex(1)
{
  token = lexer.nextToken();
}

Parser::~Parser()
{
  
}

void Parser::error(std::string message)
{
  std::cerr << message << " Found " << token->lexeme()
	    << " at line " << token->line()
	    << " position " << token->pos() << std::endl;
  exit(1);
}

void Parser::check(int tokenType, std::string message)
{
  if (token->type() != tokenType)
    error(message);
}

Parser::TreeNode* Parser::funcall(std::string functionName)
{  
  int paramCount = 0;
  token = lexer.nextToken();
  
  if (token->type() == Token::RPAREN) {
    auto argc = new Parser::TreeNode(Parser::LOADL, std::to_string(static_cast<long long>(paramCount * 8)));								     
    auto call = new Parser::TreeNode(Parser::CALL, functionName);
    auto retValue = new Parser::TreeNode(Parser::SEQ, argc, call);
    return retValue;
  }
  
  Parser::TreeNode* node = expression();
  paramCount++;  
  //node->paramCount = paramCount;
  
  while (token->type() != Token::RPAREN) {
    
    if (token->type() == Token::COMMA) {	
      paramCount++;
      token = lexer.nextToken(); // need to skip one token forward
      
      auto n2 = expression();      
      //n2->paramCount = paramCount;
      node = new Parser::TreeNode(Parser::SEQ, node, n2);	
    }
    
    if (token->type() == Token::RPAREN) {      
      break;
    }     
  }  
  
  auto argc = new Parser::TreeNode(Parser::LOADL, std::to_string(static_cast<long long>(paramCount * 8)));  
  node = new Parser::TreeNode(Parser::SEQ, node, argc);
  auto call = new Parser::TreeNode(Parser::CALL, functionName);
  node = new Parser::TreeNode(Parser::SEQ, node, call);  
  token = lexer.nextToken();
  
  return node;
}

Parser::TreeNode* Parser::factor()
{
  Parser::TreeNode* node;
  
  switch (token->type())
    {
    case Token::LPAREN:
      token = lexer.nextToken();
      node = expression();
      check(Token::RPAREN, "Expected \")\" after factor expression");
      token = lexer.nextToken();
      break;
    case Token::INTLIT:
      node = new Parser::TreeNode(Parser::LOADL, token->lexeme());
      token = lexer.nextToken();
      break;
    case Token::IDENT:
      {
	std::string str = token->lexeme();
	token = lexer.nextToken();
	
	if (token->type() == Token::LPAREN)
	  {
	    node = funcall(str);
	    break;
	  }
	else
	  {
	    int a = symTable.getUniqueSymbol(str);
	    if (!a)
	      error("Variable not defined or not in scope");
	    
	    node = new Parser::TreeNode(Parser::LOADV, std::to_string(static_cast<long long>(a)));	    
	    break;
	  }
      }
    }
  
  return node;
}

Parser::TreeNode* Parser::term()
{
  Parser::TreeNode*  node = factor();
  
  while (token->type() == Token::DIVIDE || token->type() == Token::TIMES)
    {
      if (token->type() == Token::DIVIDE) {
	token = lexer.nextToken();	
	node = new Parser::TreeNode(Parser::DIV, node, factor());
      }
      
      else if (token->type() == Token::TIMES) {
	token = lexer.nextToken();	
	node = new Parser::TreeNode(Parser::MULT, node, factor());
      }
    }
  
  return node;
}

Parser::TreeNode* Parser::expression()
{
  Parser::TreeNode* node = term();
  
  while (token->type() == Token::PLUS || token->type() == Token::MINUS)
    {
      if (token->type() == Token::PLUS) {
	token = lexer.nextToken();
	node = new Parser::TreeNode(Parser::ADD, node, term());
      }
      
      else if (token->type() == Token::MINUS) {
	token = lexer.nextToken();
	node = new Parser::TreeNode(Parser::SUB, node, term());
      }
    }
  
  return node;
}

Parser::TreeNode* Parser::relationalExpression()
{
  Parser::TreeNode* node = expression();
  
  switch (token->type())
    {
    case Token::EQ:
      token = lexer.nextToken();
      node = new Parser::TreeNode(Parser::ISEQ, node, expression());
      break;
    case Token::LT:
      token = lexer.nextToken();
      node = new Parser::TreeNode(Parser::ISLT, node, expression());
      break;
    case Token::LE:
      token = lexer.nextToken();
      node = new Parser::TreeNode(Parser::ISLE, node, expression());
      break;
    case Token::GT:
      token = lexer.nextToken();
      node = new Parser::TreeNode(Parser::ISGT, node, expression());
      break;
    case Token::GE:
      token = lexer.nextToken();
      node = new Parser::TreeNode(Parser::ISGE, node, expression());
      break;
    case Token::NE:
      token = lexer.nextToken();
      node = new Parser::TreeNode(Parser::ISNE, node, expression());
      break;
    }
  
  return node;
}

Parser::TreeNode* Parser::logicalExpression()
{
  Parser::TreeNode* node = relationalExpression();
  
  while (token->type() == Token::AND || token->type() == Token::OR)
    {
      if (token->type() == Token::AND) {
	token = lexer.nextToken();
	node = new Parser::TreeNode(Parser::AND, node, relationalExpression());
      }
      
      if (token->type() == Token::OR) {
	token = lexer.nextToken();
	node = new Parser::TreeNode(Parser::OR, node, relationalExpression());
      }
    }
  
  return node;
}

Parser::TreeNode* Parser::assignmentStatement()
{
  std::string var = token->lexeme();
  if (!symTable.getUniqueSymbol(var))
    error("Variable out of scope in assignment statement");
  
  token = lexer.nextToken();
  check(Token::ASSIGN, "Expected assignment operator after identifier");
  token = lexer.nextToken();
  
  Parser::TreeNode* logicalExpr = logicalExpression();
  check(Token::SEMICOLON, "Expected \";\" after expression ");
  token = lexer.nextToken();
  
  Parser::TreeNode* store = new Parser::TreeNode(Parser::STORE, std::to_string((long long)symTable.getUniqueSymbol(var)));
  Parser::TreeNode* node = new Parser::TreeNode(Parser::SEQ, logicalExpr, store);
  return node;
}

Parser::TreeNode* Parser::printfStatement() {
  Parser::TreeNode* paramList = NULL;
  int nparams = 0;
  check(Token::PRINTF, "Expecting printf");
  token = lexer.nextToken();
  check(Token::LPAREN, "Expecting (");
  token = lexer.nextToken();
  check(Token::STRINGLIT, "Expecting string literal");
  std::string formatString = token->lexeme();
  token = lexer.nextToken();
  
  if (token->type() == Token::COMMA) {
    token = lexer.nextToken();
    paramList = expression();
    ++nparams;
    
    while (token->type() == Token::COMMA) {
      token = lexer.nextToken();
      paramList = new TreeNode(SEQ, paramList, expression());
      ++nparams;
    }
  }
  
  check(Token::RPAREN, "Expecting )");
  token = lexer.nextToken();
  check(Token::SEMICOLON, "Expecting ;");
  token = lexer.nextToken();
  TreeNode* printStatement = new TreeNode(SEQ, paramList, new TreeNode(PRINTF, itos(nparams) + formatString));
  return printStatement;
}

Parser::TreeNode* Parser::whileStatement()
{
  token = lexer.nextToken();
  check(Token::LPAREN, "Expected \"(\" after \"while\"");
  token = lexer.nextToken();
  
  Parser::TreeNode* logicalExpr = logicalExpression();
  check(Token::RPAREN, "Expected \")\" after \"(\"");
  token = lexer.nextToken();
  Parser::TreeNode* b = block(false);
  
  std::string firstlabel = makeLabel();
  std::string secondlabel = makeLabel();
  Parser::TreeNode* L1 = new Parser::TreeNode(Parser::LABEL, firstlabel + ":");
  Parser::TreeNode* L2 = new Parser::TreeNode(Parser::LABEL, secondlabel + ":");
  
  Parser::TreeNode* JUMPF = new Parser::TreeNode(Parser::JUMPF, secondlabel);
  Parser::TreeNode* JUMP = new Parser::TreeNode(Parser::JUMP, firstlabel);
  
  Parser::TreeNode* retValue = new Parser::TreeNode(Parser::SEQ, L1, logicalExpr);
  retValue = new Parser::TreeNode(Parser::SEQ, retValue, JUMPF);
  retValue = new Parser::TreeNode(Parser::SEQ, retValue, b);
  retValue = new Parser::TreeNode(Parser::SEQ, retValue, JUMP);
  retValue = new Parser::TreeNode(Parser::SEQ, retValue, L2);
  
  return retValue;
}

Parser::TreeNode* Parser::ifStatement()
{
  token = lexer.nextToken();
  check(Token::LPAREN, "Expected \"(\" after \"if\"");
  token = lexer.nextToken();
  Parser::TreeNode* logicalExpr = logicalExpression();
  check(Token::RPAREN, "Expected \")\" after \"(\"");
  token = lexer.nextToken();
  Parser::TreeNode* thenBlock = block(false);
  
  std::string firstlabel = makeLabel();
  std::string secondlabel = makeLabel();
  
  if (token->type() == Token::ELSE) // else block exists
    {
      token = lexer.nextToken();
      Parser::TreeNode* elseBlock = block(false);
      Parser::TreeNode* JUMPF = new Parser::TreeNode(Parser::JUMPF, firstlabel);
      Parser::TreeNode* JUMP = new Parser::TreeNode(Parser::JUMP, secondlabel);
      Parser::TreeNode* L1 = new Parser::TreeNode(Parser::LABEL, firstlabel + ":");
      Parser::TreeNode* L2 = new Parser::TreeNode(Parser::LABEL, secondlabel + ":");
      
      Parser::TreeNode* node = logicalExpr;
      node = new Parser::TreeNode(Parser::SEQ, node, JUMPF);
      node = new Parser::TreeNode(Parser::SEQ, node, thenBlock);
      node = new Parser::TreeNode(Parser::SEQ, node, JUMP);
      node = new Parser::TreeNode(Parser::SEQ, node, L1);
      node = new Parser::TreeNode(Parser::SEQ, node, elseBlock);
      node = new Parser::TreeNode(Parser::SEQ, node, L2);
      return node;
    }
  
  else
    {
      Parser::TreeNode* JUMPF = new Parser::TreeNode(Parser::JUMPF, firstlabel);
      Parser::TreeNode* L1 = new Parser::TreeNode(Parser::LABEL, firstlabel + ":");
      
      Parser::TreeNode* node = logicalExpr;
      node = new Parser::TreeNode(Parser::SEQ, node, JUMPF);
      node = new Parser::TreeNode(Parser::SEQ, node, thenBlock);
      node = new Parser::TreeNode(Parser::SEQ, node, L1);
      return node;
    }
}

Parser::TreeNode* Parser::returnStatement()
{
  token = lexer.nextToken();
  Parser::TreeNode* node = logicalExpression();
  check(Token::SEMICOLON, "Expected \";\" after expression in return statement");
  token = lexer.nextToken();
  Parser::TreeNode* retn = new Parser::TreeNode(Parser::RET);
  return new Parser::TreeNode(Parser::SEQ, node, retn);
}

Parser::TreeNode* Parser::vardefStatement()
{
  Parser::TreeNode* node;
  token = lexer.nextToken();
  check(Token::IDENT, "Expected identifier after \"var\"");
  std::string varname = token->lexeme();
  token = lexer.nextToken();
  symTable.addSymbol(varname);
  // change to SEQ, vardefStatement needs no instruction, call to
  // addSymbol required
  node = new Parser::TreeNode(Parser::SEQ, std::to_string(static_cast<long long>(symTable.getUniqueSymbol(varname))));
  
  if (token->type() == Token::SEMICOLON)
    {
      token = lexer.nextToken();
      return node;
    }
  
  else if (token->type() == Token::COMMA)
    {
      while (token->type() != Token::SEMICOLON || token->type() == Token::COMMA)
	{
	  token = lexer.nextToken();
	  check(Token::IDENT, "Expected identifier after \",\"");
	  std::string multivar = token->lexeme();
	  symTable.addSymbol(multivar);
	  std::string tmp = std::to_string((long long)symTable.getUniqueSymbol(multivar));
	  node = new Parser::TreeNode(Parser::SEQ, node, new Parser::TreeNode(Parser::SEQ, tmp));
	  token = lexer.nextToken();
	}
      
      token = lexer.nextToken();
      return node;
    }
  
  else
    {
      error("Expected \";\" after identifier");
      return NULL;
    }
}

Parser::TreeNode* Parser::statement()
{
  int type = token->type();
  Parser::TreeNode* node;
  
  switch (type)
    {
    case Token::PRINTF:
      node = printfStatement();
      break;
    case Token::RETURN:
      node = returnStatement();
      break;
    case Token::VAR:
      node = vardefStatement();
      break;
    case Token::IDENT:
      node = assignmentStatement();
      break;
    case Token::WHILE:
      node = whileStatement();
      break;
    case Token::IF:
      node = ifStatement();
      break;
    }
  
  return node;
}

Parser::TreeNode* Parser::block(bool bIsFuncStart)
{
  check(Token::LBRACE, "Expected \"{\"");
  if(!bIsFuncStart)
    symTable.enterScope();
  
  token = lexer.nextToken();
  
  Parser::TreeNode* node = statement();
  while (token->type() != Token::RBRACE)
    {
      node = new Parser::TreeNode(Parser::SEQ, node, statement());
    }
  
  check(Token::RBRACE, "Expected \"}\"");
  symTable.exitScope();
  token = lexer.nextToken();
  
  return node;
}

Parser::TreeNode* Parser::parameterdef()
{
  check(Token::IDENT, "Invalid parameter, expected identifier");
  std::string s = token->lexeme();
  token = lexer.nextToken();  
  return new Parser::TreeNode(Parser::PARAM, s);
}

Parser::TreeNode* Parser::parameterdefs()
{
  Parser::TreeNode* node = NULL;
  std::stack<Parser::TreeNode*>* params = new std::stack<Parser::TreeNode*>();
  
  while (token->type() != Token::RPAREN)
    {
      node = parameterdef();
      params->push(node);
      
      if (token->type() == Token::COMMA)
	{
	  token = lexer.nextToken();
	  auto temp = parameterdef();
	  params->push(temp);
	  node = new Parser::TreeNode(Parser::SEQ, temp, node); // latest change								
	}
    }
  
  while (!params->empty())
    {
      Parser::TreeNode* p = params->top();
      p->paramCount = params->size();
      symTable.addSymbol(p->val);
      p->val = std::to_string((long long)symTable.getUniqueSymbol(p->val)); // replace string name with hTable value
      params->pop();
    }
  
  delete params;
  return node;
}

Parser::TreeNode* Parser::function()
{
  symTable.enterScope();
  Parser::TreeNode* node;
  check(Token::FUNCTION, "Function declarations must start with \"function\" keyword");
  token = lexer.nextToken();
  std::string funcName = token->lexeme();
  check(Token::IDENT, "Expected identifier after \"function\" keyword");
  token = lexer.nextToken();
  check(Token::LPAREN, "Expected \"(\" after identifier");
  token = lexer.nextToken();
  node = parameterdefs();
  check(Token::RPAREN, "Expected \")\" after parameters");
  token = lexer.nextToken();
  
  auto funct = new Parser::TreeNode(Parser::FUNC, funcName);
  if (node == NULL)
    {
      return new Parser::TreeNode(Parser::SEQ, funct, block(true));
    }
  else
    {
      auto temp = new Parser::TreeNode(Parser::SEQ, funct, node);
      temp = new Parser::TreeNode(Parser::SEQ, temp, block(true));
      return temp;
    }
}

Parser::TreeNode* Parser::compilationunit()
{
  Parser::TreeNode* node = function();
  while (token->type() != Token::ENDOFFILE)
    {
      node = new Parser::TreeNode(Parser::SEQ, node, function());
    }
  
  return node;
}

std::string Parser::TreeNode::toString(TreeNode* node)
{
  return toString0(node, 0);
}

std::string Parser::TreeNode::toString0(TreeNode* node, int spaces)
{
  static std::string blanks = "                                        ";
  std::string left = "";
  std::string right = "";
  bool isLeaf = true;
  
  if (node->leftChild != NULL) {
    left = toString0(node->leftChild, spaces + 2);
    isLeaf = false;
  }
  
  if (node->rightChild != NULL) {
    right = toString0(node->rightChild, spaces + 2);
    isLeaf = false;
  }
  
  std::string ret;
  
  if (isLeaf) {
    ret = blanks.substr(0, spaces) + ops[node->op] + "[" + node->val + "]";
  }
  else {
    ret = blanks.substr(0, spaces) + ops[node->op] + "(\n" + left + ",\n" + right + "\n" + blanks.substr(0, spaces) + ")";
  }
  
  return ret;
}

void Parser::emit(std::string s)
{
  std::cout << s << std::endl;
}

const std::string Parser::relationalInstruction(int value)
{
  switch(value)
    {
    case Parser::ISEQ:
      return "je";
    case Parser::ISNE:
      return "jne";
    case Parser::ISLT:
      return "jl";
    case Parser::ISLE:
      return "jle";
    case Parser::ISGT:
      return "jg";
    case Parser::ISGE:
      return "jge";
    default:
      std::cout << "Error in getRelationalInstruction" << std::endl;
      exit(1);
    }
}

void Parser::printRelational(int value)
{
  std::string s1=makeLabel();
  std::string s2=makeLabel();
  emit("pop rbx");
  emit("pop rax");
  emit("cmp rax,rbx");
  emit(relationalInstruction(value) + " " + s1);
  emit("mov rax,0");
  emit("jmp " + s2);
  emit(s1 + ":");
  emit("mov rax,1");
  emit(s2 + ":");
  emit("push rax");
}

int nfmts = 0;
std::string fmts[100];
int varcnt = 0;

void Parser::geninst(Parser::TreeNode* node)
{
  std::string fmt = "";
  int nparams = 0;
  const int MAXVARBYTES = 100;
  
  if (node != NULL)
    {
      geninst(node->leftChild);
      geninst(node->rightChild);
      
      switch (node->op) {      
      case SEQ:
	break;
      case LOADV:
	emit("push qword[rbp-" + std::to_string(static_cast<long long>(std::stoi(node->val) * 8)) + "]");
	break;
      case LOADL:
	emit("mov rax," + node->val);
	emit("push rax");	
	break;
      case ADD:
	emit("pop rbx");
	emit("pop rax");
	emit("add rax,rbx");
	emit("push rax");
	break;
      case SUB:
	emit("pop rbx");
	emit("pop rax");
	emit("sub rax,rbx");
	emit("push rax");
	break;
      case MULT:
	emit("pop rbx");
	emit("pop rax");
	emit("imul rbx");
	emit("push rax");      
      break;
      case DIV:
	emit("mov rdx,0");
	emit("pop rbx");
	emit("pop rax");
	emit("idiv rbx");
	emit("push rax");      
	break;
      case STORE:
	emit("pop qword[rbp-" + std::to_string(static_cast<long long>(std::stoi(node->val) * 8)) + "]");
	break;
      case AND:
	emit("pop rbx");
	emit("pop rax");
	emit("and rax,rbx");
	emit("push rax");
	break;
      case OR:
	emit("pop rbx");
	emit("pop rax");
	emit("or rax,rbx");
	emit("push rax");
	break;
      case LABEL:      
	emit(node->val);	
	break;
      case ISEQ:
	printRelational(node->op);	
	break;
      case ISNE:
	printRelational(node->op);	
	break;
      case ISLT:
	printRelational(node->op);	
	break;
      case ISLE:
	printRelational(node->op);
   	break;
      case ISGT:
	printRelational(node->op);
 	break;
      case ISGE:
	printRelational(node->op);
	break;
      case JUMP:
	emit("jmp " + node->val);
	break;
      case JUMPF:
	emit("pop rax");
	emit("cmp rax,0");
	emit("je " + node->val);	
	break;
      case JUMPT:
	emit("pop rax");
	emit("cmp rax,0");
	emit("jne " + node->val);	
	break;
      case CALL:
	emit("call " + node->val);	
	emit("pop rbx");
	emit("add rsp,rbx");
	emit("push rax");
	break;
      case FUNC:
	emit(node->val + ":");
	emit("push rbp");
	emit("mov rbp,rsp");
	emit("sub rsp," + std::to_string(static_cast<long long>(MAXVARBYTES)));
	varcnt = 0;	
	break;
      case RET:
	emit("pop rax");
	emit("add rsp," + std::to_string(static_cast<long long>(MAXVARBYTES)));
	emit("pop rbp");	
	emit("ret\n");	
	break;
      case PRINTF:
	fmt = node->val;
	nparams = fmt.at(0) - '0';
	fmt = "`" + fmt.substr(1) + "`";
	fmts[nfmts++] = fmt;
	emit(" mov rdi,fmt" + itos(nfmts));
	if (nparams == 5) {
	  emit(" pop r9");
	  --nparams;
	}
	if (nparams == 4) {
	  emit(" pop r8");
	  --nparams;
	}
	if (nparams == 3) {
	  emit(" pop rcx");
	  --nparams;
	}
	if (nparams == 2) {
	  emit(" pop rdx");
	  --nparams;
	}
	if (nparams == 1) {
	  emit(" pop rsi");
	}
	emit(" mov rax,0");
	emit(" push rbp");
	emit(" call printf");
	emit(" pop rbp");	
	break;
      case PARAM:
	++varcnt;
	//emit("# paramCount: " + std::to_string((long long)node->paramCount));
	emit("mov rsi,qword[rbp+" + std::to_string(static_cast<long long>((node->paramCount + 2) * 8)) + "]");
	emit("mov qword[rbp-" + std::to_string(static_cast<long long>(varcnt * 8)) + "],rsi");
	break;
      default:
	std::cerr << "In geninst: Unknown operation " << node->op << std::endl;
	exit(1);      
      }
    }
}

void Parser::genasm(Parser::TreeNode* node)
{
  emit("\tglobal main");
  emit("\textern printf\n");
  emit("\tsection .text\n");
  
  geninst(node);
  
  std::cout << std::endl << " section .data" << std::endl;
  for (int i=0; i < nfmts; ++i) {
    std::cout << " fmt" << i+1 << ": db " << fmts[i] << ", 0" << std::endl;
  }
}

void Parser::gensasm(Parser::TreeNode *node) {
  std::string fmt = "";
  if (node != NULL) {
    gensasm(node->leftChild);
    gensasm(node->rightChild);
    
    switch (node->op) {
    case SEQ:
      break;
    case LOADV:
      std::cout << ("LOADV " + node->val) << std::endl;
      break;
    case LOADL:
      std::cout << ("LOADL " + node->val) << std::endl;
      break;
    case ADD:
      std::cout << ("ADD") << std::endl;
      break;
    case SUB:
      std::cout << ("SUB") << std::endl;
      break;
    case MULT:
      std::cout << ("MULT") << std::endl;
      break;
    case DIV:
      std::cout << ("DIV") << std::endl;
      break;
    case STORE:
      std::cout << ("STORE " + node->val) << std::endl;
      break;
    case AND:
      std::cout << ("AND") << std::endl;
      break;
    case OR:
      std::cout << ("OR") << std::endl;
      break;
    case LABEL:
      std::cout << (node->val) << std::endl;
      break;
    case ISEQ:
      std::cout << ("ISEQ") << std::endl;
      break;
    case ISNE:
      std::cout << ("ISNE") << std::endl;
      break;
    case ISLT:
      std::cout << ("ISLT") << std::endl;
      break;
    case ISLE:
      std::cout << ("ISLE") << std::endl;
      break;
    case ISGT:
      std::cout << ("ISGT") << std::endl;
      break;
    case ISGE:
      std::cout << ("ISGE") << std::endl;
      break;
    case JUMP:
      std::cout << ("JUMP " + node->val) << std::endl;
      break;
    case JUMPF:
      std::cout << ("JUMPF " + node->val) << std::endl;
      break;
    case JUMPT:
      std::cout << ("JUMPT " + node->val) << std::endl;
      break;
    case CALL:
      std::cout << ("CALL " + node->val) << std::endl;
      break;
    case FUNC:
      std::cout << ("FUNC " + node->val) << std::endl;      
      break;
    case RET:
      std::cout << ("RET ") << std::endl;
      break;
    case PRINTF:
      std::cout << ("PRINTF '" + node->val + "'") << std::endl;
      break;
    case PARAM:
      std::cout << ("PARAM " + node->val) << std::endl;      
      break;
    default:
      std::cerr << "In gensasm: Unknown operation " << node->op << std::endl;
      exit(1);
      break;      
    }
  }
}
