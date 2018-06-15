#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "lexer.h"
#include "SymbolTable.h"

#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <sstream>

class Parser {
  
  enum Operation {
    ADD, SUB, MULT, DIV, // Arithmetic Operators
    ISEQ, ISNE, ISLT, ISLE, ISGT, ISGE, // Relational Operators
    AND, OR, // Logical Operators
    LOADL, LOADV, STORE, // Value Transfer Instructions
    JUMP, JUMPF, JUMPT, CALL, RET, // Location Transfer Instructions
    PRINTF, // Misc
    LABEL, SEQ, // Pseudo Operations
    FUNC, PARAM // new Operations
  };
  
public:
  class TreeNode;
  
  TreeNode* funcall(std::string functionName);
  TreeNode* factor();
  TreeNode* term();
  TreeNode* expression();
  TreeNode* relationalExpression();
  TreeNode* logicalExpression();
  TreeNode* assignmentStatement();
  TreeNode* returnStatement();
  TreeNode* printfStatement();
  TreeNode* whileStatement();
  TreeNode* ifStatement();
  TreeNode* assignStatement();
  TreeNode* vardefStatement();
  TreeNode* statement();
  TreeNode* block(bool bIsFuncStart);
  TreeNode* parameterdef();
  TreeNode* parameterdefs();
  TreeNode* function();
  TreeNode* compilationunit();

  void emit(std::string s);
  void printRelational(int value);  
  const std::string relationalInstruction(int value);
  
  void geninst(Parser::TreeNode* node);
  void genasm(Parser::TreeNode* node);
  void gensasm(Parser::TreeNode * node);
  
  Parser(Lexer& lexer, std::ostream& out);
  ~Parser();
  
  // Parser::TreeNode
  class TreeNode {
  public:
    Operation op;
    std::string val; // Variable name or jump label
    TreeNode *leftChild;
    TreeNode *rightChild;
    int paramCount;
    
    // Utility function used by constructors
    void init(Operation opx, std::string valx, TreeNode *leftChildx, TreeNode *rightChildx) {
      op = opx;
      val = valx;
      leftChild = leftChildx;
      rightChild = rightChildx;
      paramCount = 0;
    }
    
    TreeNode(Operation op, std::string val) {
      init(op, val, NULL, NULL);
    }
    
    TreeNode(Operation op, std::string val, TreeNode *leftChild, TreeNode *rightChild) {
      init(op, val, leftChild, rightChild);
    }
    
    TreeNode(Operation op) {
      init(op, "", NULL, NULL);
    }
    
    TreeNode(Operation op, TreeNode *leftChild, TreeNode *rightChild) {
      init(op, "", leftChild, rightChild);
    }
    
    static std::string toString(TreeNode *node);
    static std::string toString0(TreeNode *node, int spaces);
  };
  
private:
  Lexer& lexer;
  Token* token;
  std::ostream& out;
  int lindex;
  int tindex;
  SymbolTable symTable;
  
  std::string itos(int i) {
    std::stringstream ss;
    ss << i;
    std::string res = ss.str();
    return res;
  }
  
  std::string makeLabel() {
    std::string tmp = "L";
    std::stringstream ss;
    ss << ++lindex;
    std::string res = ss.str();
    tmp = tmp + res;
    return tmp;
  }

  static const std::string ops[];
  
  void error(std::string message);
  void check(int tokenType, std::string message);
};

#endif
