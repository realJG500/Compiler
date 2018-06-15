// Compile with '-std=c++0x' ;; required for various c++11 features

#include "token.h"
#include "lexer.h"
#include "parser.h"
#include <iostream>
#include <fstream>

void processFile(std::istream& in) {
  Lexer lexer(in);
  Parser parser(lexer, std::cout);
  Parser::TreeNode* program = parser.compilationunit();
  //std::cout << Parser::TreeNode::toString(program) << std::endl;
  parser.genasm(program);
}

int main(int argc, char **argv) {
  std::ifstream in;
  
  if (argc > 1) {
    in.open(argv[1]);
    processFile(in);
    in.close();
  }
  else {
    processFile(std::cin);
  }
  
  return 0;
}
