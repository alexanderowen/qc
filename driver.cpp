/* Author: Alexander Owen
 *
 * Driver program for the Quack compiler. 
 *
 * Take a Quack file as input and compiles it. 
 * Produces an executable called 'pgm' which is the compile Quack program
 * */

#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <iostream>

#include "TranslatorVisitor.hpp"
#include "TypeTree.hpp"
#include "visitors.hpp"
#include "nodes.hpp"
#include "lex.yy.h"
#include "grammar.tab.h"

#define DEBUG 0

extern FILE *yyin;
extern int yyparse();
extern Program *root;

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return -1;
    }

    FILE *myfile = fopen(argv[1], "r");
    if (!myfile) 
    {
        fprintf(stderr, "I can't open file!\n");
        return -1;
    }

    int condition;
    yyin = myfile;
#ifdef DEBUG
    fprintf(stderr, "Beginning parse of %s\n", argv[1]);
#endif
    
    // Parse the file, performing lexical and syntax analysis
    // Root of the AST stored in 'root'
    condition = yyparse();
    if (condition != 0)
        return -1;

    // Begin Semantic analysis
    // Check class hierarchy structure (inheriting properly)
    if (!root->checkClassHierarchy())
    {
        fprintf(stderr, "Error: Class hierarchy is malformed\n");
        return 0;
    } 

    // Check constructor calls, make classes were defined
    ConstructorVisitor cv;
    root->accept(&cv);
    if (!cv.checkStructure())
    {
        fprintf(stderr, "Error: Call to constructor that is not defined\n");
        return 0;
    }

    // Construct the type tree
    TypeTreeVisitor ttv;
    root->accept(&ttv);    

    // Perform static type checking 
    TypeCheckVisitor tcv(ttv.tt);
    root->accept(&tcv);
    if (tcv.errors > 0)
    {
        for (list<char*>::const_iterator it = tcv.msgs.begin(); it != tcv.msgs.end(); ++it)
        {
            fprintf(stderr, "%s:", argv[0]);
            fprintf(stderr, "%s\n", (*it));
        }
        fprintf(stderr, "%d errors reported\n", tcv.errors);
        return -1;
    }

    if (condition != 0)
    {
        return -1;
    }

    // Begin code generation
    TranslatorVisitor tv((char*)"q.c", tcv.tt, tcv.st);
    root->accept(&tv);

    fclose(tv.f);
    system("gcc -c q.c");
    system("gcc q.o Builtins.o -o pgm");
    delete root;

    return 0;
}
