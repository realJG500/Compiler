OPTS= -g -c -Wall -Werror -std=c++0x

microc: microc.o parser.o token.o lexer.o SymbolTable.o
	g++ -o microc microc.o parser.o token.o lexer.o SymbolTable.o

SymbolTable.o: SymbolTable.cc SymbolTable.h
	g++ $(OPTS) SymbolTable.cc

microc.o: microc.cc lexer.o
	g++ $(OPTS) microc.cc

parser.o: parser.h parser.cc
	g++ $(OPTS) parser.cc

lextest.o: lextest.cc
	g++ $(OPTS) lextest.cc

lexer.o: lexer.h lexer.cc
	g++ $(OPTS) lexer.cc

token.o: token.h token.cc
	g++ $(OPTS) token.cc

clean:
	rm -rf *~ *.o *.asm *.sasm lextest microc