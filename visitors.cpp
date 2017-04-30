/* Author: Alexander Owen
 *
 * visitors.cpp implements the following visitor classes: Visitor, ConstructorVisitor, 
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
#include <list>
#include <iostream>
#include <algorithm>
#include <iterator>

#include <stdio.h>
#include <stdlib.h>

#include "visitors.hpp"
#include "string.h"
#include "nodes.hpp"
#include "TypeTree.hpp"
#include "util.hpp"

using std::list;


/*********************
 *
 * Defining Visitor methods
 *
 ***********************/

void Visitor::visitProgram(Program *p) 
{
    for (list<Class *>::const_iterator it = p->classes->begin(); it != p->classes->end(); ++it)
    {
        (*it)->accept(this);
    }
    for (list<Statement *>::const_iterator it = p->statements->begin(); it != p->statements->end(); ++it)
    {
        (*it)->accept(this);
    }
}

void Visitor::visitClass(Class *c) 
{
    c->clssig->accept(this);
    c->clsbdy->accept(this);
}

void Visitor::visitFalseExtendsOption(FalseExtendsOption *f) {}
void Visitor::visitTrueExtendsOption(TrueExtendsOption *t) {}
void Visitor::visitFormalArg(FormalArg *f) {}

void Visitor::visitClassSignature(ClassSignature *cs) 
{
    for (list<FormalArg *>::const_iterator it = cs->fargs->begin(); it != cs->fargs->end(); ++it)
    {
        (*it)->accept(this);
    }
    cs->exop->accept(this);
}

void Visitor::visitClassBody(ClassBody *cb) 
{
    for (list<Statement *>::const_iterator it = cb->stmts->begin(); it != cb->stmts->end(); ++it)
    {
        (*it)->accept(this);
    }
    for (list<Method *>::const_iterator it = cb->meths->begin(); it != cb->meths->end(); ++it)
    {
        (*it)->accept(this);
    }
}

void Visitor::visitFalseIdentOption(FalseIdentOption *f) {}
void Visitor::visitTrueIdentOption(TrueIdentOption *t) {}

void Visitor::visitMethod(Method *m) 
{
    for (list<FormalArg *>::const_iterator it = m->fargs->begin(); it != m->fargs->end(); ++it)
    {
        (*it)->accept(this);
    }
    m->ident->accept(this);
    for (list<Statement *>::const_iterator it = m->stmts->begin(); it != m->stmts->end(); ++it)
    {
        (*it)->accept(this);
    }
}

void Visitor::visitEmptyRExpr(EmptyRExpr *e) {}
void Visitor::visitDotRExpr(DotRExpr *d) 
{
    d->rexpr->accept(this);
    for (list<RExpr *>::const_iterator it = d->args->begin(); it != d->args->end(); ++it)
    {
        (*it)->accept(this);
    }
}    

void Visitor::visitConstructorRExpr(ConstructorRExpr *c) 
{
    for (list<RExpr *>::const_iterator it = c->args->begin(); it != c->args->end(); ++it)
    {
        (*it)->accept(this);
    }
}

void Visitor::visitRExprToLExpr(RExprToLExpr *rl) 
{
    rl->lexpr->accept(this);
}

void Visitor::visitStringNode(StringNode *s) {}
void Visitor::visitIntNode(IntNode *i) {}

void Visitor::visitNotNode(NotNode *n) 
{
    n->value->accept(this);
}

void Visitor::visitBinaryOperatorNode(BinaryOperatorNode *b) 
{
    b->left->accept(this);
    b->right->accept(this);
}

void Visitor::visitRExprStatement(RExprStatement *r) 
{
    r->rexpr->accept(this);
}

void Visitor::visitReturnStatement(ReturnStatement *r) 
{
    r->rexpr->accept(this);
}

void Visitor::visitAssignmentStatement(AssignmentStatement *a) 
{
    a->lexpr->accept(this);
    a->ident->accept(this);
    a->rexpr->accept(this);
}

void Visitor::visitWhileStatement(WhileStatement *w) 
{
    w->rexpr->accept(this);
    for (list<Statement *>::const_iterator it = w->stmts->begin(); it != w->stmts->end(); ++it)
    {
        (*it)->accept(this);
    }
}

void Visitor::visitIfBlock(IfBlock *i) 
{
    i->_if->accept(this);
    for (list<ElifClause *>::const_iterator it = i->_elifs->begin(); it != i->_elifs->end(); ++it)
    {
        (*it)->accept(this);
    }
    i->_else->accept(this);
}

void Visitor::visitIfClause(IfClause *i) 
{
    i->rexpr->accept(this);
    for (list<Statement *>::const_iterator it = i->stmts->begin(); it != i->stmts->end(); ++it)
    {
        (*it)->accept(this);
    }
}

void Visitor::visitElifClause(ElifClause *e) 
{
    e->rexpr->accept(this);
    for (list<Statement *>::const_iterator it = e->stmts->begin(); it != e->stmts->end(); ++it)
    {
        (*it)->accept(this);
    }
}

void Visitor::visitFalseElseOption(FalseElseOption *e) {}
void Visitor::visitTrueElseOption(TrueElseOption *e) 
{
    for (list<Statement *>::const_iterator it = e->stmts->begin(); it != e->stmts->end(); ++it)
    {
        (*it)->accept(this);
    }
}

void Visitor::visitIdentNode(IdentNode *i) {}

void Visitor::visitObjectFieldLExpr(ObjectFieldLExpr *o) 
{
    o->rexpr->accept(this);
}


/*********************
 *
 * Defining ConstructorVisitor methods
 *
 ***********************/

ConstructorVisitor::ConstructorVisitor() 
{
    classes.push_back((char *)"Obj");
    classes.push_back((char *)"Int");
    classes.push_back((char *)"String");
    classes.push_back((char *)"Nothing");
}

ConstructorVisitor::~ConstructorVisitor() {}
void ConstructorVisitor::visitConstructorRExpr(ConstructorRExpr *c)
{
    if (!withinList(&constructors, c->id))
        constructors.push_back(c->id);
    for (list<RExpr *>::const_iterator it = c->args->begin(); it != c->args->end(); ++it)
    {
        (*it)->accept(this);
    }
}
void ConstructorVisitor::visitClassSignature(ClassSignature *cs)
{
    classes.push_back(cs->id);
    for (list<FormalArg *>::const_iterator it = cs->fargs->begin(); it != cs->fargs->end(); ++it)
    {
        (*it)->accept(this);
    }
    cs->exop->accept(this);
}

bool ConstructorVisitor::checkStructure()
{
    for (list<char *>::const_iterator it = constructors.begin(); it != constructors.end(); ++it)
    {
        if (!withinList(&classes, (*it)))
            return false;
    }
    return true;
}
void ConstructorVisitor::print()
{
    std::cout << "Constructors: "; 
    std::copy(std::begin(constructors), std::end(constructors), std::ostream_iterator<char *>(std::cout, " "));
    std::cout << "\n" << std::endl;
    std::cout << "Classes: ";
    std::copy(std::begin(classes), std::end(classes), std::ostream_iterator<char *>(std::cout, " "));
    std::cout << "\n" << std::endl;
}

/*********************
 *
 * Defining TypeTreeVisitor methods
 *
 ***********************/

TypeTreeVisitor::TypeTreeVisitor()
{
    tt = new TypeTree();
    cur = NULL;
    ret = NULL;
    args = NULL;

    inMethod = false;
}

void TypeTreeVisitor::visitProgram(Program *p) 
{
    for (list<Class *>::const_iterator it = p->classes->begin(); it != p->classes->end(); ++it)
    {
        (*it)->accept(this);
    }
}

void TypeTreeVisitor::visitClassSignature(ClassSignature *cs) 
{
    cur = strdup(cs->id); //current class working on
    for (list<FormalArg *>::const_iterator it = cs->fargs->begin(); it != cs->fargs->end(); ++it)
    {
        (*it)->accept(this);
    }
    cs->exop->accept(this);
}

void TypeTreeVisitor::visitFalseExtendsOption(FalseExtendsOption *f) 
{
    tt->addSubtype(cur, strdup((char*)"Obj"));
}

void TypeTreeVisitor::visitTrueExtendsOption(TrueExtendsOption *t) 
{
    int f = tt->addSubtype(cur, t->id);
}

void TypeTreeVisitor::visitMethod(Method *m)
{
    inMethod = true;
    args = new list<char*>;
    for (list<FormalArg *>::const_iterator it = m->fargs->begin(); it != m->fargs->end(); ++it)
    {
        (*it)->accept(this);
    }

    m->ident->accept(this);
    MethodNode *meth = new MethodNode(m->id, *args, ret);
    tt->addMethodToType(cur, meth);
    inMethod = false;
}

void TypeTreeVisitor::visitFormalArg(FormalArg *f) 
{
    if (inMethod)
        args->push_back(f->type);
}

void TypeTreeVisitor::visitFalseIdentOption(FalseIdentOption *f) 
{
    ret = strdup((char*)"Nothing");
}

void TypeTreeVisitor::visitTrueIdentOption(TrueIdentOption *t) 
{
    ret = t->id;
}


/*********************
 *
 * Defining TypeCheckVisitor methods
 *
 ***********************/

TypeCheckVisitor::TypeCheckVisitor()
{
    st = new SymbolTable(NULL);
    // Adding the built in 'variables'
    VariableSym *t = new VariableSym(strdup((char*)"true"), strdup((char*)"Boolean"));
    st->addVariable(strdup((char*)"true"), t);
    VariableSym *f = new VariableSym(strdup((char*)"false"), strdup((char*)"Boolean"));
    st->addVariable(strdup((char*)"false"), f);

    tt = new TypeTree();    
    errors = 0;

    inMethod = false;
    inMethodReturnCheck = false;
    returnType = NULL;
    returned = false;

    inClass = false;
    className = NULL;
    supertype = NULL;

    mustRepeat = false;
}
TypeCheckVisitor::TypeCheckVisitor(TypeTree *t)
{
    st = new SymbolTable(NULL);
    // Adding the built in 'variables'
    VariableSym *tr = new VariableSym(strdup((char*)"true"), strdup((char*)"Boolean"));
    st->addVariable(strdup((char*)"true"), tr);
    VariableSym *f = new VariableSym(strdup((char*)"false"), strdup((char*)"Boolean"));
    st->addVariable(strdup((char*)"false"), f);

    tt = t;
    errors = 0;

    inMethod = false;
    inMethodReturnCheck = false;
    returnType = NULL;
    returned = false;
}
TypeCheckVisitor::~TypeCheckVisitor() {}

// Has the type checker met the max number of errors?
bool TypeCheckVisitor::check()
{
    return (errors > 10) ? true : false;
}

void TypeCheckVisitor::visitProgram(Program *p)
{
    for (list<Class *>::const_iterator it = p->classes->begin(); it != p->classes->end(); ++it)
    {
        (*it)->accept(this);
    }
    SymbolTable *origin = st;
    st = new SymbolTable(origin);

    for (list<Statement *>::const_iterator it = p->statements->begin(); it != p->statements->end(); ++it)
    {
        (*it)->accept(this);
    }
    p->st = st;
    st = origin;
}

void TypeCheckVisitor::visitBinaryOperatorNode(BinaryOperatorNode *b)
{
    if (check())
        return;
    b->left->accept(this);
    b->right->accept(this);
    char *t1 = getType(b->left);
    char *t2 = getType(b->right);
    if (t1 == NULL || t2 == NULL)
    {
        return;
    }
    if (strcmp(t1, (char*)"-") == 0 || strcmp(t2, (char*)"-") == 0)
    {
        fprintf(stderr, "Compiler error. I don't know the types of this binary operator\n");
    }

    if (strcmp(t1, t2) != 0)
    {
        char *msg = (char*) malloc(sizeof(char)*256);
        sprintf(msg, "%d: Syntax Error\n\tBinary opeartor type mismatch: '%s' and '%s'\n", b->lineno, t1, t2);
        addError(msg);
    }

    char *op;

    switch(b->operation) {
        case 0:
            op = (char*)"PLUS";
            break;
        case 1:
            op = (char*)"MINUS";
            break;
        case 2:
            op = (char*)"TIMES";
            break;
        case 3:
            op = (char*)"DIVIDE";
            break;
        case 4:
            op = (char*)"EQUALS";
            break;
        case 5:
            op = (char*)"ATMOST";
            break;
        case 6:
            op = (char*)"LESS";
            break;
        case 7:
            op = (char*)"ATLEAST";
            break;
        case 8:
            op = (char*)"MORE";
            break;
        case 9:
            op = (char*)"AND";
            break;
        case 10:
            op = (char*)"OR";
            break;
        default:
            break;
    }
    MethodNode *method = tt->typeGetMethod(t1, op);
    if (method == NULL)
    {
        char *msg = (char*) malloc(sizeof(char)*256);
        sprintf(msg, "%d: Syntax Error\n\tType '%s' has no operator named '%s'\n", b->lineno, t1, op);
        addError(msg);
    } 
}
   
void TypeCheckVisitor::visitAssignmentStatement(AssignmentStatement *a)
{
    char *type;
    IdentNode *id = dynamic_cast<IdentNode*>(a->lexpr);
    if (id != NULL)
    {
        VariableSym *defined = st->lookupVariable(id->id);
        TrueIdentOption *tio = dynamic_cast<TrueIdentOption*>(a->ident);
        if (tio != NULL && defined != NULL)
        {
            type = tt->LCA(tio->id, getType(a->rexpr));
            type = tt->LCA(defined->type, type);
        }
        else if (defined != NULL) // If this variable has already been defined, perform LCA
        {
            bool changed = false;
            type = tt->LCA(defined->type, getType(a->rexpr));    
            if (type == NULL)
            {
                type = defined->type;
            } 
            else if (strcmp(defined->type, getType(a->rexpr)) != 0)
            {
                changed = true;
            }
            st->removeVariable(defined); //remove old value 
            if (inWhile && changed && strcmp(type, (char*)"Obj") != 0) //the type changed and we're in a while loop
            {
                mustRepeat = true;
            }
        }
        else if (tio != NULL)
        {
            type = tt->LCA(tio->id, getType(a->rexpr));
        }
        else 
        {
            type = getType(a->rexpr);
        }
        if (type == NULL)
            return;
        VariableSym *v = new VariableSym(id->id, strdup(type));
        st->addVariable(strdup(id->id), v);
    }
    ObjectFieldLExpr *ofl = dynamic_cast<ObjectFieldLExpr*>(a->lexpr);
    if (ofl != NULL) 
    {
        IdentNode *ident = isIdent(ofl->rexpr);
        if (ident != NULL)
        {
            if (strcmp(ident->id, (char*)"this") == 0)
            {
                VariableNode *v = new VariableNode(strdup(ofl->id), strdup(getType(a->rexpr)));
                tt->addVarToType(strdup(className), v);
            }
        } 
    }
    a->lexpr->accept(this);
    a->ident->accept(this);
    a->rexpr->accept(this);
}

void TypeCheckVisitor::visitIdentNode(IdentNode *i) 
{
    if (strcmp(i->id, (char*)"this") == 0) {
        return;
    }
}

void TypeCheckVisitor::visitDotRExpr(DotRExpr *d)
{
    // visit first, collect args
    list<char*> args;
    d->rexpr->accept(this);
    for (list<RExpr *>::const_iterator it = d->args->begin(); it != d->args->end(); ++it)
    {
        (*it)->accept(this);
        args.push_back(getType((*it)));
    }
    // now type check
    char *type;
    type = getType(d->rexpr);
    MethodNode *m = tt->typeGetMethod(type, d->id);
    if (m == NULL)
    {
        errors++;
        char *msg = (char*) malloc(sizeof(char)*256);
        sprintf(msg, "%d: Syntax Error\n\tType '%s' has no method named '%s'\n", d->lineno, type, d->id);
        msgs.push_back(msg);
    } 
    else  
    { 
        if (m->argsType.size() != args.size())
        {
            char *msg = (char*) malloc(sizeof(char)*256);
            sprintf(msg, "%d: Syntax Error\n\tInvalid call to method '%s'; not enough arguments supplied\n", d->lineno, d->id);
            addError(msg);
            return;
        }

        list<char*>::const_iterator methodArgs = m->argsType.begin();
        list<char*>::const_iterator arg = args.begin(); 
        for (int i = 0; i < m->argsType.size(); i++)
        {
            if (strcmp((*methodArgs), (*arg)) != 0)
            {
                if (!tt->isSubtype((*arg),(*methodArgs)))
                {
                    char *msg = (char*) malloc(sizeof(char)*256);
                    sprintf(msg, "%d: Syntax Error\n\tMethod call argument at position %d is not the same type or a subtype of required argument\n", d->lineno, i+1);
                    addError(msg);
                }
            }
            std::advance(methodArgs, 1);
            std::advance(arg, 1);
        }
    }
}

void TypeCheckVisitor::visitConstructorRExpr(ConstructorRExpr *c)
{
    for (list<RExpr *>::const_iterator it = c->args->begin(); it != c->args->end(); ++it)
    {
        (*it)->accept(this);
    }
}

void TypeCheckVisitor::visitIfBlock(IfBlock *i)
{
    list<SymbolTable*> sts;
    SymbolTable *origin = st;
    st = new SymbolTable(origin);
    sts.push_back(st);

    i->_if->accept(this);
    SymbolTable *if_st = st;

    list<SymbolTable *> elif_sts;
    for (list<ElifClause *>::const_iterator it = i->_elifs->begin(); it != i->_elifs->end(); ++it)
    {
        st = new SymbolTable(origin);
        sts.push_back(st);
        (*it)->accept(this);
        elif_sts.push_back(st);
    }

    SymbolTable *else_st;
    TrueElseOption *tso = dynamic_cast<TrueElseOption*>(i->_else);
    if (tso != NULL)
    {
        st = new SymbolTable(origin);
        sts.push_back(st);
        i->_else->accept(this);
        else_st = st;
    } 
    else 
    {
        else_st = if_st;
    }

    st = sts.front()->intersection(sts, tt);
    st->merge(origin);

    // This removes the higher level variables from the local-if sym table
    i->_if->st = if_st->remove(if_st, st);

    auto iter = elif_sts.begin();
    for (list<ElifClause *>::const_iterator it = i->_elifs->begin(); it != i->_elifs->end(); ++it)
    {
        (*it)->st = (*iter)->remove((*iter), st);
        iter++;
    }
    
    i->_else->st = else_st->remove(else_st, st);
}

void TypeCheckVisitor::visitIfClause(IfClause *i)
{
    char *type;
    type = getType(i->rexpr);

    if (strcmp(type, (char*)"Boolean") != 0)
    {
        char *msg = (char*) malloc(sizeof(char)*256);
        sprintf(msg, "%d: Syntax Error\n\tIf condition must be of type 'Boolean'\n", i->lineno);
        addError(msg);
    }
    i->rexpr->accept(this);
    for (list<Statement *>::const_iterator it = i->stmts->begin(); it != i->stmts->end(); ++it)
    {
        (*it)->accept(this);
    }
}

void TypeCheckVisitor::visitElifClause(ElifClause *e)
{
    char *type;
    type = getType(e->rexpr);

    if (strcmp(type, (char*)"Boolean") != 0)
    {
        char *msg = (char*) malloc(sizeof(char)*256);
        sprintf(msg, "%d: Syntax Error\n\tElif condition must be of type 'Boolean'\n", e->lineno);
        addError(msg);
    }
    e->rexpr->accept(this);
    for (list<Statement *>::const_iterator it = e->stmts->begin(); it != e->stmts->end(); ++it)
    {
        (*it)->accept(this);
    }
}

void TypeCheckVisitor::visitTrueElseOption(TrueElseOption *e)
{
    for (list<Statement *>::const_iterator it = e->stmts->begin(); it != e->stmts->end(); ++it)
    {
        (*it)->accept(this);
    }
}

void TypeCheckVisitor::visitWhileStatement(WhileStatement *w)
{
    inWhile = true;
    char *type = getType(w->rexpr);
    if (type != NULL && strcmp(type, (char*)"Boolean") != 0)
    {
        char *msg = (char*) malloc(sizeof(char)*256);
        sprintf(msg, "%d: Syntax Error\n\tWhile condition must be of type 'Boolean'\n", w->lineno);
        addError(msg);
    }
    w->rexpr->accept(this);
    for (list<Statement *>::const_iterator it = w->stmts->begin(); it != w->stmts->end(); ++it)
    {
        (*it)->accept(this);
        while (mustRepeat)
        {
            mustRepeat = false;
            (*it)->accept(this);
        }
    }
    w->st = st;
    inWhile = false;
}

void TypeCheckVisitor::visitMethod(Method *m)
{
    inMethod = true;
    SymbolTable *origin = st;
    st = new SymbolTable(origin); //scope for Methods

    // check if it's inherited, and if it's doing it properly
    MethodNode *superMethod = tt->typeGetMethod(supertype, m->id);
    if (superMethod != NULL)
    {
        MethodNode *override = tt->typeGetMethod(className, m->id);
        if (superMethod->argsType.size() != override->argsType.size())
        {
            char *msg = (char*) malloc(sizeof(char)*256);
            sprintf(msg, "%d: Syntax Error\n\tOverridden method '%s' does not have the correct number of arguments\n", m->lineno, m->id);
            addError(msg);
        }
        else //check that the args and return type are overridden correctly
        {
            list<char*>::const_iterator superArgs = superMethod->argsType.begin();                                           
            list<char*>::const_iterator overrideArgs = override->argsType.begin();                                              
            for (int i = 0; i < superMethod->argsType.size(); i++)                                                              
            {                                                                                                  
                if (strcmp((*superArgs), (*overrideArgs)) != 0)                                                    
                {
                    if (!tt->isSupertype((*overrideArgs),(*superArgs)))
                    {
                        char *msg = (char*) malloc(sizeof(char)*256);
                        sprintf(msg, "%d: Syntax Error\n\tMethod argument override at position %d is not the same type or supertype of overridden method\n", m->lineno, i+1);
                        addError(msg);
                    }
                }
                std::advance(superArgs, 1);
                std::advance(overrideArgs, 1);
            }
            //check return statement
            if (strcmp(superMethod->returnType, override->returnType) != 0)
            {
                if (!tt->isSubtype(override->returnType, superMethod->returnType))
                {
                    char *msg = (char*) malloc(sizeof(char)*256);
                    sprintf(msg, "%d: Syntax Error\n\tReturn value of override method is not the same type or subtype of overridden method\n", m->lineno);
                    addError(msg);
                }
            }
        }        
    }
    //
    for (list<FormalArg *>::const_iterator it = m->fargs->begin(); it != m->fargs->end(); ++it)
    {
        (*it)->accept(this);
    }
    inMethodReturnCheck = true;
    m->ident->accept(this);
    inMethodReturnCheck = false;
    for (list<Statement *>::const_iterator it = m->stmts->begin(); it != m->stmts->end(); ++it)
    {
        (*it)->accept(this);
    }

    if (!returned)
    {
        char *msg = (char*) malloc(sizeof(char)*256);
        sprintf(msg, "%d: Syntax Error\n\tMethod '%s' does not return value of type '%s'\n", m->lineno, m->id, returnType);
        addError(msg);
    }
    inMethod = false;
    returned = false;
    m->st = st;
    st = origin;
}

void TypeCheckVisitor::visitTrueIdentOption(TrueIdentOption *t)
{
    if (inMethodReturnCheck)
    {
        if (strcmp(t->id, (char*)"Nothing") == 0)
        {
            returned = true;  //assume method returns nothing
        }
        returnType = t->id;
    }
}

void TypeCheckVisitor::visitFalseIdentOption(FalseIdentOption *f)
{
    if (inMethodReturnCheck)
    {
        returnType = strdup((char*)"Nothing");
        returned = true; // by default, assume the method returns nothing
    }
}

void TypeCheckVisitor::visitReturnStatement(ReturnStatement *r)
{
    if (!inMethod)
    {
        char *msg = (char*) malloc(sizeof(char)*256);
        sprintf(msg, "%d: Syntax Error\n\tReturn statement outside of method declaration\n", r->lineno);
        addError(msg);
        return; 
    }
    char *type;
    r->rexpr->accept(this);
    type = getType(r->rexpr);

    if (strcmp(type, returnType) != 0)
    {
        if (!tt->isSubtype(type, returnType))
        {
            char *msg = (char*) malloc(sizeof(char)*256);
            sprintf(msg, "%d: Syntax Error\n\tMethod returns value of type '%s', should return '%s' or a subtype of '%s'\n", r->lineno, type, returnType, returnType);
            addError(msg);
        }
    } 
    else 
    {
        returned = true;
    }
}

void TypeCheckVisitor::visitClass(Class *c) 
{
    inClass = true;
    className = c->getID();
    supertype = c->getExtends();

    SymbolTable *classScope = new SymbolTable(st);
    beyondConstructorScope = st;
    st = classScope;

    c->clssig->accept(this);
    c->clsbdy->accept(this);

    inClass = false;
}

void TypeCheckVisitor::visitClassSignature(ClassSignature *cs) 
{
    for (list<FormalArg *>::const_iterator it = cs->fargs->begin(); it != cs->fargs->end(); ++it)
    {
        (*it)->accept(this);
    }
    cs->exop->accept(this);
}

void TypeCheckVisitor::visitClassBody(ClassBody *cb)  
{
    for (list<Statement *>::const_iterator it = cb->stmts->begin(); it != cb->stmts->end(); ++it)
    {
        (*it)->accept(this);
    }
    cb->st = st; //need to save st for code gen
    /* We need a way for the constructor of a class to throw out arguments, and keep 'this'
     * instance variables. We define the 'classScope' as only for the constructor. We escape 
     * the class scope once this is done. Instance variables are retained because they 
     * exist in the TypeTree. */
    st = beyondConstructorScope;
    for (list<Method *>::const_iterator it = cb->meths->begin(); it != cb->meths->end(); ++it)
    {
        (*it)->accept(this);
    }
}

void TypeCheckVisitor::visitFormalArg(FormalArg *f)
{
    VariableSym *v = new VariableSym(strdup(f->id), strdup(f->type));
    st->addVariable(strdup(f->id), v);
}

void TypeCheckVisitor::addError(char *msg)
{
    errors++;
    msgs.push_back(msg);
}

IdentNode *TypeCheckVisitor::isIdent(RExpr *r)
{
    RExprToLExpr *rl = dynamic_cast<RExprToLExpr*>(r);
    if (rl != NULL) //if it is an lexpr
    {
        IdentNode *id = dynamic_cast<IdentNode*>(rl->lexpr);
        if (id != NULL) //and the lexpr is an ident node
        {
            return id; 
        }
    }
    return NULL;

}

ObjectFieldLExpr *TypeCheckVisitor::isOFL(RExpr *r)
{
    RExprToLExpr *rl = dynamic_cast<RExprToLExpr*>(r);
    if (rl != NULL) //if it is an lexpr
    {
        ObjectFieldLExpr *ofl = dynamic_cast<ObjectFieldLExpr*>(rl->lexpr);
        if (ofl != NULL)
        {
            return ofl;
        }
    }
    return NULL;
}

char *TypeCheckVisitor::getType(RExpr *r)
{
    char *type;
    type = r->type();
    if (strcmp(type, (char*)"-") != 0) //type covered because it's a literal or easy to identify
        return type;

    IdentNode *ident = isIdent(r);
    if (ident != NULL) //type is in the variable information
    {
        if (strcmp(ident->id, (char*)"this") == 0)
        {
            return className;
        }
        VariableSym *v = st->lookupVariable(ident->id);
        if (v == NULL)
        {
            char *msg = (char*) malloc(sizeof(char)*256);
            sprintf(msg, "%d: Syntax Error\n\tUse of uninitialized variable '%s'\n", r->lineno, ident->id);
            addError(msg);
            return NULL;
        }
        return v->type;
    }

    DotRExpr *dot = dynamic_cast<DotRExpr*>(r);
    if (dot != NULL)
    {
        char *_type = getType(dot->rexpr);
        MethodNode *m = tt->typeGetMethod(_type, dot->id);
        if (m == NULL)
        {
            return strdup((char*)"-");
        }
        return m->returnType;
    }

    ObjectFieldLExpr *ofl = isOFL(r);
    if (ofl != NULL)
    {
        char *rType = getType(ofl->rexpr);
        if (rType == NULL)
            return strdup((char*)"-");
        char *__type = tt->getVarFromType(rType, ofl->id);
        if (__type == NULL)
        {
            char *msg = (char*) malloc(sizeof(char)*256);
            sprintf(msg, "%d: Syntax Error\n\tType '%s' has no instance variable '%s'\n", r->lineno, rType, ofl->id);
            addError(msg);
            return strdup((char*)"-");
        }
        return __type;
    }

    PlusNode *plus = dynamic_cast<PlusNode*>(r);
    if (plus != NULL)
    {
        return getType(plus->left);
    }
    MinusNode *minus = dynamic_cast<MinusNode*>(r);
    if (minus != NULL)
    {
        return getType(minus->left);
    }
    TimesNode *times = dynamic_cast<TimesNode*>(r);
    if (times != NULL)
    {
        return getType(times->left);
    }
    DivideNode *divide = dynamic_cast<DivideNode*>(r);
    if (divide != NULL)
    {
        return getType(divide->left);
    }

    return strdup((char*)"-");
}
