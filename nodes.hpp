/* Author: Alexander Owen
 *
 * node.hpp defines the nodes that comprise the abstract syntax tree (AST) used during 
 * type checking. 
 *
 * Each node represents a grammatical structure in the language. 
 *
 * */
#ifndef NODE_H
#define NODE_H

#include <list>

#include <stdio.h>

#include "SymbolTable.hpp"

using std::list;

class Visitor; 

/* ********
 *
 * Listed below are the classes defined in this file
 * They comprise the nodes of the AST
 *
 * ********/
class Node;
class Class;
class ClassSignature;
class ClassBody;
class ExtendsOption;
class TrueExtendsOption;  /*Note: By the end of the project, I have determined
                            that it would have been better to resolve True/False options
                            with maybe a NULL pointer, or a bool field in ExtendsOption. */
class FalseExtendsOption;
class FormalArg;
class Method;
class IdentOption;
class TrueIdentOption;
class FalseIdentOption;
class ActualArgs;
class RExpr;
class EmptyRExpr;
class DotRExpr;
class ConstructorRExpr;
class RExprToLExpr;
class StringNode;
class IntNode;
class NotNode;
class BinaryOperatorNode;
class PlusNode;   /* By the end of the project, I suspect that instead of making
                   * each binary operator it's own node, it may have been better 
                   * to have 1 BinaryOperatorNode, with a field that determines
                   * the operation 
                   * */
class MinusNode;
class TimesNode;
class DivideNode;
class LessThanNode;
class GreaterThanNode;
class EqualsNode;
class AtMostNode;
class AtLeastNode;
class AndNode;
class OrNode;
class Statement;
class ReturnStatement;
class AssignmentStatement;
class RExprStatement;
class WhileStatement;
class IfBlock;
class IfClause;
class ElifClause;
class ElseOption;
class TrueElseOption;
class FalseElseOption;
class LExpr;
class IdentNode;
class ObjectFieldLExpr;
class Program;

/* 
 * Below are the definitions of the above classes
 * 
 */


// The base class which all AST-nodes are derived
class Node 
{
    public:
        int lineno;
        SymbolTable *st;

        Node(int l);
        Node() {lineno = 0;}
        void setLineno(int l);
};

class Class : public Node 
{
    public:
        ClassSignature *clssig;
        ClassBody *clsbdy;

        Class(ClassSignature *cs, ClassBody *cb);
        virtual ~Class();

        virtual void print();
        virtual void accept(Visitor *v);
        char *getID();
        char *getExtends();
};

class ExtendsOption : public Node 
{
    public:
        virtual void print() = 0;
        virtual char *getID() = 0;
        virtual void accept(Visitor *v) = 0;
};

class FalseExtendsOption : public ExtendsOption
{
    public:
        FalseExtendsOption();

        virtual void print();
        virtual char *getID();
        virtual void accept(Visitor *v);
};


class TrueExtendsOption : public ExtendsOption
{
    public:
        char *id;

        TrueExtendsOption(char *i);
        virtual void print();
        virtual void accept(Visitor *v);
        virtual char *getID();
};

class FormalArg : public Node 
{
    public:
        char *id;
        char *type;

        FormalArg(char *i, char *t);
        virtual void print();
        virtual void accept(Visitor *v);
};

class ClassSignature : public Node 
{
    public:
        char *id;
        list<FormalArg *> *fargs;
        ExtendsOption *exop;

        ClassSignature(char *i, list<FormalArg *> *f, ExtendsOption *e);
        virtual void print();
        virtual void accept(Visitor *v);
        char *getID();
        char *getExtends();
};

class ClassBody : public Node 
{
    public:
        list<Statement *> *stmts;
        list<Method *> *meths;

        ClassBody(list<Statement *> *s, list<Method *> *m);
        virtual void print();
        virtual void accept(Visitor *v);
};

class IdentOption : public Node
{
    public:
        virtual ~IdentOption();

        virtual void print() = 0;
        virtual void accept(Visitor *v) = 0;

};

class FalseIdentOption : public IdentOption
{
    public:
        FalseIdentOption();
        virtual void print();
        virtual void accept(Visitor *v);
};

class TrueIdentOption : public IdentOption
{
    public:
        char *id;

        TrueIdentOption(char *i);
        virtual ~TrueIdentOption();
        virtual void print();
        virtual void accept(Visitor *v);
};

class Method : public Node 
{
    public:
        char *id;
        list<FormalArg *> *fargs;
        IdentOption *ident;
        list<Statement *> *stmts;

        Method(char *, list<FormalArg *> *, IdentOption *, list<Statement *> *);
        virtual void print(); 
        virtual void accept(Visitor *v);
};


/*****************
 * RExpr classes *
 *****************/

class RExpr : public Node  //ABC
{
    public:
        virtual ~RExpr();

        virtual void print() = 0;
        virtual void accept(Visitor *v) = 0;
        virtual char *type();
};

class EmptyRExpr : public RExpr
{
    public:
        EmptyRExpr();
        virtual void print();
        virtual void accept(Visitor *v);
        virtual char *type();
};

class DotRExpr : public RExpr
{
    public:
        RExpr         *rexpr;
        char          *id;
        list<RExpr *> *args;

        DotRExpr(RExpr *r, char *i, list<RExpr *> *a);
        virtual void print();
        virtual void accept(Visitor *v);
};

class ConstructorRExpr : public RExpr
{
    public:
        char *id;
        list<RExpr *> *args;

        ConstructorRExpr(char *i, list<RExpr *> *a);
        virtual void print();
        virtual void accept(Visitor *v);
        virtual char *type();
};

class RExprToLExpr : public RExpr
{
    public:
        LExpr *lexpr;

        RExprToLExpr(LExpr *l);
        virtual void print();
        virtual void accept(Visitor *v);
};

class StringNode : public RExpr
{
    public:
        char *id;

        StringNode(char *i);
        virtual void print(); 
        virtual void accept(Visitor *v);
        virtual char *type();
};

class IntNode : public RExpr
{
    public:
        int value;

        IntNode(int i);

        virtual void print(); 
        virtual void accept(Visitor *v);
        virtual char *type();
};

class NotNode : public RExpr
{
    public:
        RExpr *value;

        NotNode(RExpr* v);
        void print();
        virtual void accept(Visitor *v);
        virtual char *type();
};



class BinaryOperatorNode : public RExpr
{
    public:
        RExpr *left;
        RExpr *right;
        int operation; /* Field set by subclasses to determine what the binary op is 
                        *  plus:     0 
                        *  minus:    1 
                        *  times:    2 
                        *  divide:   3  
                        *  equals:   4 
                        *  atmost:   5 
                        *  lessthan: 6 
                        *  atleast:  7 
                        *  greater:  8 
                        *  and:      9 
                        *  or:       10
                        */

        BinaryOperatorNode(RExpr *l, RExpr *r, int o);
        virtual ~BinaryOperatorNode();

        virtual void accept(Visitor *v);
        virtual char *type();
};

class PlusNode : public BinaryOperatorNode
{
    public:
        PlusNode(RExpr *l, RExpr *r);
        virtual void print();
};

class MinusNode : public BinaryOperatorNode
{
    public:
        MinusNode(RExpr *l, RExpr *r);
        virtual void print();
};

class TimesNode : public BinaryOperatorNode
{
    public:
        TimesNode(RExpr *l, RExpr *r);
        virtual void print();
};

class DivideNode : public BinaryOperatorNode
{
    public:
        DivideNode(RExpr *l, RExpr *r);
        virtual void print();
};

class EqualsNode : public BinaryOperatorNode
{
    public:
        EqualsNode(RExpr *l, RExpr *r);
        virtual void print();
        virtual char *type();
};

class AtMostNode : public BinaryOperatorNode
{
    public:
        AtMostNode(RExpr *l, RExpr *r);
        virtual void print();
        virtual char* type();
};

class LessThanNode : public BinaryOperatorNode
{
    public:
        LessThanNode(RExpr *l, RExpr *r);
        virtual void print();
        virtual char* type();
};

class AtLeastNode : public BinaryOperatorNode
{
    public:
        AtLeastNode(RExpr *l, RExpr *r);
        virtual void print();
        virtual char* type();
};

class GreaterThanNode : public BinaryOperatorNode
{
    public:
        GreaterThanNode(RExpr *l, RExpr *r);
        virtual void print();
        virtual char* type();
};

class AndNode : public BinaryOperatorNode
{
    public:
        AndNode(RExpr *l, RExpr *r);
        virtual void print();
        virtual char* type();
};

class OrNode : public BinaryOperatorNode
{
    public:
        OrNode(RExpr *l, RExpr *r);
        virtual void print();
        virtual char* type();
};


/**********
 * Statement classes
 * ********/

class Statement : public Node
{
    public:
        virtual ~Statement();

        virtual void print() = 0;
        virtual void accept(Visitor *v) = 0;
};

class RExprStatement : public Statement 
{
    public:
        RExpr *rexpr;

        RExprStatement(RExpr* r);
        virtual ~RExprStatement();

        virtual void print(); 
        virtual void accept(Visitor *v);
};

class ReturnStatement : public Statement
{
    public:
        RExpr *rexpr;

        ReturnStatement(RExpr *r);
        virtual ~ReturnStatement();
        
        virtual void print();
        virtual void accept(Visitor *v);
};

class AssignmentStatement : public Statement
{
    public:
        LExpr       *lexpr;
        IdentOption *ident;
        RExpr       *rexpr;

        AssignmentStatement(LExpr *l, IdentOption *i, RExpr *r);
        virtual ~AssignmentStatement();
        virtual void print();
        virtual void accept(Visitor *v);
};

class WhileStatement : public Statement 
{
    public:
        RExpr *rexpr;
        list<Statement *> *stmts;

        WhileStatement(RExpr *r, list<Statement *> *s);
        virtual ~WhileStatement();

        virtual void print();
        virtual void accept(Visitor *v);
}; 


class IfBlock : public Statement 
{
    public:
        IfClause *_if;
        list<ElifClause *> *_elifs;
        ElseOption *_else;

        IfBlock(IfClause *i, list<ElifClause *> *ei, ElseOption *el);
        virtual void print();
        virtual void accept(Visitor *v);
};

class IfClause : public Node 
{
    public:
        RExpr *rexpr;
        list<Statement *> *stmts;

        IfClause(RExpr *r, list<Statement *> *stmts);
        virtual void print();
        virtual void accept(Visitor *v);
};

class ElifClause : public Node 
{
    public:
        RExpr *rexpr;
        list<Statement *> *stmts;

        ElifClause(RExpr *r, list<Statement *> *stmts);
        virtual void print();
        virtual void accept(Visitor *v);
};

class ElseOption : public Node
{
    public:
        virtual void print() = 0;
        virtual void accept(Visitor *v) = 0;
};

class FalseElseOption : public ElseOption
{
    public:
        FalseElseOption();
        virtual void print();
        virtual void accept(Visitor *v);
};

class TrueElseOption : public ElseOption
{
    public:
        list<Statement *> *stmts;

        TrueElseOption(list<Statement *> *s);
        virtual void print();
        virtual void accept(Visitor *v);
};


/***************
 * LExpr classes
 * *************/

class LExpr : public Node
{
    public:
        virtual ~LExpr();

        virtual void print() = 0;
        virtual void print(FILE *);
        virtual void accept(Visitor *v) = 0;
};

class IdentNode : public LExpr
{
    public:
        char *id;

        IdentNode(char *i);
        virtual ~IdentNode();

        virtual void print();
        virtual void print(FILE *);
        virtual void accept(Visitor *v);
};

class ObjectFieldLExpr : public LExpr
{
    public:
        RExpr *rexpr;
        char  *id;

        ObjectFieldLExpr(RExpr *r, char *i);
        virtual void print();
        virtual void accept(Visitor *v);
};

class Program : public Node 
{
    public:
        list<Statement *> *statements;
        list<Class *>     *classes;

        Program(list<Class *> *c, list<Statement *> *s, int);
        virtual ~Program();

        bool checkClassHierarchy();
        virtual void accept(Visitor *v);
};

#endif
