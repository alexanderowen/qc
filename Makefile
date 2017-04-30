quack: grammar.tab.o lex.yy.o nodes.o visitors.o util.o SymbolTable.o TypeTree.o TranslatorVisitor.o driver.o 
	g++ driver.o lex.yy.o grammar.tab.o nodes.o visitors.o util.o SymbolTable.o TypeTree.o TranslatorVisitor.o -o qc -ll
	gcc -c Builtins.c

mc: 
	gcc -c Builtins.c
	gcc -c q.c
	gcc q.o Builtins.o


TranslatorVisitor.o: TranslatorVisitor.hpp TranslatorVisitor.cpp
	g++ -c -std=c++11 TranslatorVisitor.cpp

driver.o: driver.cpp
	g++ -c -std=c++11 driver.cpp

TypeTree.o: TypeTree.hpp TypeTree.cpp
	g++ -std=c++11 -c -g TypeTree.cpp

SymbolTable.o: SymbolTable.hpp SymbolTable.cpp
	g++ -std=c++11 -c -g SymbolTable.cpp

util.o: util.hpp util.cpp
	g++ -std=c++11 -c util.cpp -I.

visitors.o: visitors.hpp visitors.cpp
	g++ -std=c++11 -c -g visitors.cpp -I.

nodes.o: nodes.cpp nodes.hpp
	g++ -std=c++11 -c -g nodes.cpp -I.

grammar.tab.o: grammar.y
	bison -d grammar.y
	g++ -std=c++11 -c -g grammar.tab.c

lex.yy.o: lexer.lex 
	flex lexer.lex
	g++ -c -g lex.yy.c


clean:
	rm *.o
