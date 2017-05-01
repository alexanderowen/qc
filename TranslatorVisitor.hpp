/* Author: Alexander Owen
 *
 * The TranslatorVisitor is a subtype of Visitor. Traverses the AST to 
 * produce C code to generate. 
 *
 * Separated from visitors.hpp because this is used during code generation, 
 * not type checking. 
 *
 * */

#ifndef TRANSLATORVISITOR_H
#define TRANSLATORVISITOR_H

#include "stdio.h"

#include <unordered_map>
#include <string>

#include "visitors.hpp"
#include "TypeTree.hpp"

using std::unordered_map;
using std::string;

class TranslatorVisitor : public Visitor 
{
    private:
        unordered_map<string, string> typeMap;
        unordered_map<string, string> keywords;
        TypeTree *tt;
        SymbolTable *st;

        list<string> printed;
        list<string> methodPrinted;

        char *className;
        unordered_map<string, string> classMethods;

        bool inMethod;

        IdentNode *isIdent(RExpr *);
        ObjectFieldLExpr *isOFL(RExpr *);
        char *getType(RExpr *);
        void printRExpr(RExpr *);

        // Given a TypeNode, print it's methods
        void printMethodSignatures(TypeNode *);
        void getMethodNames(TypeNode *);

    public:
        FILE *f = NULL;

        TranslatorVisitor(char *, TypeTree *, SymbolTable *);
       ~TranslatorVisitor(); 

        void visitProgram(Program *);

        void visitClass(Class *);
        void visitClassSignature(ClassSignature *);
        void visitClassBody(ClassBody *);
        void visitFormalArg(FormalArg *);
        void visitMethod(Method *);
        void visitTrueIdentOption(TrueIdentOption *);
        void visitFalseIdentOption(FalseIdentOption *);
        void visitAssignmentStatement(AssignmentStatement *);
        void visitReturnStatement(ReturnStatement *);
        void visitIfClause(IfClause *);
        void visitElifClause(ElifClause *);
        void visitTrueElseOption(TrueElseOption *);
        void visitWhileStatement(WhileStatement *);
        void visitConstructorRExpr(ConstructorRExpr *);
        void visitIntNode(IntNode *);
        void visitStringNode(StringNode *);
        void visitNotNode(NotNode *);
        void visitBinaryOperatorNode(BinaryOperatorNode *);
        void visitIdentNode(IdentNode *);
        void visitObjectFieldLExpr(ObjectFieldLExpr *);
        void visitDotRExpr(DotRExpr *);
};

#endif 
