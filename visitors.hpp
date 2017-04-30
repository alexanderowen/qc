/* Author: Alexander Owen
 *
 * visitors.hpp defines the following visitor classes: Visitor, ConstructorVisitor, 
 * TypeTreeVisitor, and TypeCheckVisitor 
 *
 * Each visitor is constructed to follow the visitor pattern
 *
 * Visitor: base class from which all visitors are derived
 * ConstructorVisitor: traverses the AST, checks that constructor calls are valid
 * TypeTreeVisitor: traverses the AST, constructs the type tree
 * TypeCheckVisitor: traverses the AST, performs static type checking
 *
 * */ 
#ifndef VISITOR_H 
#define VISITOR_H

#include <list>

#include <stdio.h>

#include "nodes.hpp"
#include "SymbolTable.hpp"
#include "TypeTree.hpp"

using std::list;

/* Visitor defines a visitor that traverses the AST without doing
 * any meaningful analysis
 *
 * */
class Visitor
{
    public:
    virtual void visitProgram(Program *p);
    virtual void visitClass(Class *c);
    virtual void visitFalseExtendsOption(FalseExtendsOption *f);
    virtual void visitTrueExtendsOption(TrueExtendsOption *t);
    virtual void visitFormalArg(FormalArg *f);
    virtual void visitClassSignature(ClassSignature *cs);
    virtual void visitClassBody(ClassBody *cb);
    virtual void visitFalseIdentOption(FalseIdentOption *f);
    virtual void visitTrueIdentOption(TrueIdentOption *t);
    virtual void visitMethod(Method *m);
    virtual void visitEmptyRExpr(EmptyRExpr *e);
    virtual void visitDotRExpr(DotRExpr *d);    
    virtual void visitConstructorRExpr(ConstructorRExpr *c);
    virtual void visitRExprToLExpr(RExprToLExpr *rl);
    virtual void visitStringNode(StringNode *s);
    virtual void visitIntNode(IntNode *i);
    virtual void visitNotNode(NotNode *n);
    virtual void visitBinaryOperatorNode(BinaryOperatorNode *b);
    virtual void visitRExprStatement(RExprStatement *r);
    virtual void visitReturnStatement(ReturnStatement *r);
    virtual void visitAssignmentStatement(AssignmentStatement *a);
    virtual void visitWhileStatement(WhileStatement *w);
    virtual void visitIfBlock(IfBlock *i);
    virtual void visitIfClause(IfClause *i);
    virtual void visitElifClause(ElifClause *e);
    virtual void visitFalseElseOption(FalseElseOption *e);
    virtual void visitTrueElseOption(TrueElseOption *e);
    virtual void visitIdentNode(IdentNode *i);
    virtual void visitObjectFieldLExpr(ObjectFieldLExpr *o);
};


/* The ConstructorVisitor checks for proper usage of calls to
 * constructor methods. 
 *
 * */
class ConstructorVisitor : public Visitor
{
    private:
        list<char *> constructors;
        list<char *> classes;
    public:
        ConstructorVisitor();
        ~ConstructorVisitor();
        virtual void visitConstructorRExpr(ConstructorRExpr *c);
        virtual void visitClassSignature(ClassSignature *cs);
        bool checkStructure();
        void print();
};

/* The TypeTreeVisitor visits the AST to build up the TypeTree so
 * it can be used during type checking
 *
 * */
class TypeTreeVisitor : public Visitor
{
    public:
        TypeTree *tt;
        char *cur; //current class visiting
        char *ret; //current return value of method
        list<char*> *args; 
        bool inMethod;

        TypeTreeVisitor();
        virtual void visitProgram(Program *p);
        virtual void visitClassSignature(ClassSignature *cs);
        virtual void visitFalseExtendsOption(FalseExtendsOption *f);
        virtual void visitTrueExtendsOption(TrueExtendsOption *t);
        virtual void visitMethod(Method *m);
        virtual void visitFormalArg(FormalArg *f);
        virtual void visitFalseIdentOption(FalseIdentOption *f);
        virtual void visitTrueIdentOption(TrueIdentOption *t);
};

/* The TypeCheckVisitor performs static type checking on the AST
 *
 * */
class TypeCheckVisitor : public Visitor
{
    public:
        typedef Visitor super;
        SymbolTable *st;
        TypeTree *tt;

    public:
        int errors;
        list<char*> msgs;

        TypeCheckVisitor();
        TypeCheckVisitor(TypeTree *t);
        ~TypeCheckVisitor();
    
        bool check(); 
        void addError(char *msg);
        virtual void visitProgram(Program *);
        virtual void visitBinaryOperatorNode(BinaryOperatorNode *b);
        virtual void visitAssignmentStatement(AssignmentStatement *a);
        virtual void visitIdentNode(IdentNode *i);
        virtual void visitDotRExpr(DotRExpr *d);    
        virtual void visitConstructorRExpr(ConstructorRExpr *);

        virtual void visitIfBlock(IfBlock *i);
        virtual void visitIfClause(IfClause *i);
        virtual void visitElifClause(ElifClause *e);
        virtual void visitTrueElseOption(TrueElseOption *e);
        virtual void visitWhileStatement(WhileStatement *w);

        virtual void visitMethod(Method *m);
        virtual void visitFalseIdentOption(FalseIdentOption *f);
        virtual void visitTrueIdentOption(TrueIdentOption *t);
        virtual void visitReturnStatement(ReturnStatement *r);

        virtual void visitClass(Class *c);
        virtual void visitClassSignature(ClassSignature *cs);
        virtual void visitClassBody(ClassBody *cb);
        virtual void visitFormalArg(FormalArg *f);

    private:

        bool inMethod;
        bool inMethodReturnCheck;
        char *returnType;
        bool returned;
        
        bool inClass;
        char *className;
        char *supertype;

        bool inWhile;
        bool mustRepeat;

        SymbolTable *beyondConstructorScope;

        IdentNode *isIdent(RExpr *r);
        ObjectFieldLExpr *isOFL(RExpr *r);

        char *getType(RExpr *r);
};

#endif
