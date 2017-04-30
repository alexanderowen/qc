/* Author: Alexander Owen
 *
 * TypeTree.cpp implements the type tree to be used by the Quack typechecker
 *
 * The TypeTree defines the class hierarchy of a Quack program
 * It is comprised of TypeNodes, which contains information about the 
 * methods and instance variables of the type.
 *
 * */

#include <list>

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "TypeTree.hpp"

using std::list;


/* The TypeTree defines, in its constructor, the builtin types and methods of Quack
 *
 * */
TypeTree::TypeTree()
{
    OBJ     = strdup((char*)"Obj");
    INT     = strdup((char*)"Int");
    STR     = strdup((char*)"String");
    BOOL    = strdup((char*)"Boolean");
    NOTHING = strdup((char*)"Nothing");

    TypeNode *o = new TypeNode(OBJ, NULL);
    root = o;

    list<char*> emptyArgs;

    // Assigning build-in methods of Obj to TypeTree
    list<char*> objArgs;
    objArgs.push_back(OBJ);
    MethodNode *m = new MethodNode(strdup((char*)"STR"), emptyArgs, STR);
    this->addMethodToType(OBJ, m);
    MethodNode *ObjPrint = new MethodNode(strdup((char*)"PRINT"), emptyArgs, NOTHING);
    this->addMethodToType(OBJ, ObjPrint); 
    MethodNode *ObjEquals = new MethodNode(strdup((char*)"EQUALS"), objArgs, BOOL);
    this->addMethodToType(OBJ, ObjEquals);

    // Assignment built-in methods of Int to TypeTree
    root->addChild(INT);
    list<char*> int_args;
    int_args.push_back(INT);
    MethodNode *IntPlus = new MethodNode(strdup((char*)"PLUS"), int_args, INT);
    this->addMethodToType(INT, IntPlus);
    MethodNode *IntMinus = new MethodNode(strdup((char*)"MINUS"), int_args, INT);
    this->addMethodToType(INT, IntMinus);
    MethodNode *IntTimes = new MethodNode(strdup((char*)"TIMES"), int_args, INT);
    this->addMethodToType(INT, IntTimes);
    MethodNode *IntDivide = new MethodNode(strdup((char*)"DIVIDE"), int_args, INT);
    this->addMethodToType(INT, IntDivide);
    MethodNode *IntAtMost = new MethodNode(strdup((char*)"ATMOST"), int_args, BOOL);
    this->addMethodToType(INT, IntAtMost);
    MethodNode *IntLess = new MethodNode(strdup((char*)"LESS"), int_args, BOOL);
    this->addMethodToType(INT, IntLess);
    MethodNode *IntAtLeast = new MethodNode(strdup((char*)"ATLEAST"), int_args, BOOL);
    this->addMethodToType(INT, IntAtLeast);
    MethodNode *IntMore = new MethodNode(strdup((char*)"MORE"), int_args, BOOL);
    this->addMethodToType(INT, IntMore);

    // Methods for String
    root->addChild(STR);
    list<char*> str_args;
    str_args.push_back(STR);
    MethodNode *StrPlus = new MethodNode(strdup((char*)"PLUS"), str_args, STR);
    this->addMethodToType(STR, StrPlus);
    MethodNode *StrAtMost = new MethodNode(strdup((char*)"ATMOST"), str_args, BOOL);
    this->addMethodToType(STR, StrAtMost);
    MethodNode *StrLess = new MethodNode(strdup((char*)"LESS"), str_args, BOOL);
    this->addMethodToType(STR, StrLess);
    MethodNode *StrAtLeast = new MethodNode(strdup((char*)"ATLEAST"), str_args, BOOL);
    this->addMethodToType(STR, StrAtLeast);
    MethodNode *StrMore = new MethodNode(strdup((char*)"MORE"), str_args, BOOL);
    this->addMethodToType(STR, StrMore);

    // Methods for Bool
    root->addChild(BOOL);
    list<char*> bool_args;
    bool_args.push_back(BOOL);
    MethodNode *BoolNot = new MethodNode(strdup((char*)"NOT"), bool_args, BOOL);
    this->addMethodToType(BOOL, BoolNot);
    MethodNode *BoolAnd = new MethodNode(strdup((char*)"AND"), bool_args, BOOL);
    this->addMethodToType(BOOL, BoolAnd);
    MethodNode *BoolOr  = new MethodNode(strdup((char*)"OR" ), bool_args, BOOL);
    this->addMethodToType(BOOL, BoolOr);

    // No methods for 'Nothing' type
    root->addChild(NOTHING);
}

TypeTree::~TypeTree()
{
    free(OBJ);
    free(INT);
    free(STR);
    free(BOOL);
    free(NOTHING);
    
    delete root;
}

bool TypeTree::addSubtype(TypeNode *sub, char *super)
{
    TypeNode *type = findType(super);
    if (type == NULL)
        return false;

    type->addChild(sub);
    return true;
}

bool TypeTree::addSubtype(char *sub, char *super)
{
    TypeNode *n = new TypeNode(sub, NULL);
    return this->addSubtype(n, super);
}

bool TypeTree::addMethodToType(char *_type, MethodNode *m)
{
    TypeNode *type = findType(_type);
    if (type == NULL)
        return false;

    type->addMethod(m);
    return true;
}

bool TypeTree::addVarToType(char *type, VariableNode *v)
{
    TypeNode *t = findType(type);
    if (t == NULL)
        return false;

    t->addInstanceVar(v, this);
    return true;
}

/* Is 't1' a subtype of 't2'?
 * */
bool TypeTree::isSubtype(char *_t1, char *_t2)
{
    TypeNode *t1 = findType(_t1);
    TypeNode *t2 = findType(_t2);
    if (t1 == NULL || t2 == NULL)
        return false;

    return t2->hasDescendant(_t1);
}


/* Is 't1' a supertype of 't2'?
 * */
bool TypeTree::isSupertype(char *_t1, char *_t2)
{
    TypeNode *t1 = findType(_t1); //do they exist in the first place?
    TypeNode *t2 = findType(_t2);
    if (t1 == NULL || t2 == NULL)
        return false;

    return t1->hasDescendant(_t2); 
}

/* Find the name of the least common ancestor between two types
 * */
char *TypeTree::LCA(char *_t1, char *_t2)
{
    TypeNode *t1 = findType(_t1); //do they exist in the first place?
    TypeNode *t2 = findType(_t2);
    if (t1 == NULL || t2 == NULL)
        return NULL;

    TypeNode *t2origin = t2;

    if (t1->equals(t2))
        return t1->name;

    while (strcmp(t1->name, (char*)"Obj") != 0)
    {
        while (strcmp(t2->name, (char*)"Obj") != 0)
        {
            if (t1->equals(t2))
                return t1->name;
            t2 = t2->parent;
        }
        t1 = t1->parent;
        t2 = t2origin;
    }

    return this->root->name; //The top level ancestor
}

/* Does '_type' have a method named 'method'?
 * */
bool TypeTree::typeHasMethod(char *_type, char *method)
{
    TypeNode *type = findType(_type);
    if (type == NULL)
        return false;
    return type->hasMethod(method);
}

/* Returns the type of the instance variable 'var' that belongs to 'type'
 * */
char *TypeTree::getVarFromType(char *type, char *var)
{
    TypeNode *t = findType(type);
    if (t == NULL)
        return NULL;

    VariableNode *v = t->getInstanceVar(var);
    if (v == NULL)
        return NULL;

    return v->type;
}

/* Return the MethodNode named 'method' from type named '_type'
 * Returns NULL if no such MethodNode
 * */
MethodNode *TypeTree::typeGetMethod(char *_type, char *method)
{
    TypeNode *type = findType(_type);
    if (type == NULL)
        return NULL;
    return type->getMethod(method);
}

/* Return the TypeNode named 'name'
 * Returns NULL if no such TypeNode
 * */
TypeNode *TypeTree::findType(char *name)
{
    return search(root, name);
}

/* Recursively searches the TypeTree for a TypeNode named 'name'
 * Returns NULL if no such TypeNode
 * */
TypeNode *TypeTree::search(TypeNode *r, char *name)
{
    if (r->equals(name))
        return r;
    for (list<TypeNode *>::const_iterator it = r->children.begin(); it != r->children.end(); ++it)
    {
        TypeNode *t = search((*it), name);
        if (t != NULL)
            return t;
    }
    return NULL;
}

void TypeTree::print()
{
    this->print(root); 
}

void TypeTree::print(TypeNode *t)
{
    t->print();
    for (list<TypeNode *>::const_iterator it = t->children.begin(); it != t->children.end(); ++it)
    {
        printf("Children of %s:\n", t->name);
        print((*it));
    }
}   



/******** TypeNode methods ********/
TypeNode::TypeNode(char *n, TypeNode *p) : name(n), parent(p) {}

TypeNode::~TypeNode()
{
    for (list<MethodNode*>::const_iterator it = methods.begin(); it != methods.end(); ++it)
    {
        delete (*it);
    }
    if (parent != NULL)
        delete parent;
}


bool TypeNode::hasInstanceVar(char *name)
{
    for (list<VariableNode*>::const_iterator it = instanceVars.begin(); it != instanceVars.end(); ++it)
    {
        if (strcmp((*it)->name, name) == 0)
            return true;
    }
    return false;
}

//TODO: Has no way of knowing if this variable should be trashed
//      as a result of it being defined in a bad if/elif/else declaration tree
//      It is handled outside of regular variables by the SymbolTable structure
void TypeNode::addInstanceVar(VariableNode *v, TypeTree *tt)
{
    VariableNode *_v = this->getInstanceVar(v->name);
    if (_v != NULL)
    {
        _v->type = tt->LCA(_v->type, v->type);
    }
    else 
    {
        instanceVars.push_back(v);
    }
}

VariableNode *TypeNode::getInstanceVar(char *name)
{
    for (list<VariableNode*>::const_iterator it = instanceVars.begin(); it != instanceVars.end(); ++it)
    {
        if (strcmp((*it)->name, name) == 0)
            return (*it);
    }
    return NULL;
}


void TypeNode::addChild(char *name)
{
    TypeNode *n = new TypeNode(name, NULL);
    this->addChild(n);
}

void TypeNode::addChild(TypeNode *type)
{
    children.push_back(type);  
    type->parent = this;
}

/* Does this TypeNode have a (direct or indirect) subtype named 'type'
 * */
bool TypeNode::hasDescendant(char *type)
{
    for (list<TypeNode*>::const_iterator it = children.begin(); it != children.end(); ++it)
    {
        if (strcmp((*it)->name, type) == 0 || (*it)->hasDescendant(type))
            return true;
    }
    return false;
}

void TypeNode::addMethod(MethodNode *m)
{
    methods.push_back(m);
}

bool TypeNode::hasMethod(char *name)
{
    for (list<MethodNode *>::const_iterator it = this->methods.begin(); it != this->methods.end(); ++it)
    {
        if ( strcmp((*it)->id, name) == 0)
            return true;
    }
    if (this->parent != NULL)
        return parent->hasMethod(name);

    return false;
}

MethodNode *TypeNode::getMethod(char *name)
{
    for (list<MethodNode *>::const_iterator it = this->methods.begin(); it != this->methods.end(); ++it)
    {
        if ( strcmp((*it)->id, name) == 0)
            return (*it);
    }
    if (this->parent != NULL) //follow inheritance tree
    {
        return parent->getMethod(name);
    }
    return NULL;
}

int TypeNode::equals(TypeNode *type)
{
    return strcmp(this->name, type->name) == 0;
}

int TypeNode::equals(char *n)
{
    return strcmp(this->name, n) == 0;
}

void TypeNode::print()
{
    printf("Type: %s\n",this->name);
    for (list<MethodNode*>::const_iterator it = methods.begin(); it != methods.end(); ++it)
    {
        (*it)->print();
    }

}

/******** MethodNode methods ********/

MethodNode::MethodNode(char *i, list<char*> a, char *r) : id(i), argsType(a), returnType(r) {}

MethodNode::~MethodNode()
{
    free(id);    
}

void MethodNode::print()
{
    fprintf(stderr, "  Method: '%s' takes: '", id);
    for (list<char*>::const_iterator it = argsType.begin(); it != argsType.end(); ++it)
    {
        printf("%s ", (*it));
    }
    printf("' and returns '%s'\n", returnType);
}

bool MethodNode::equals(MethodNode *m)
{
    if (strcmp(m->id, id) == 0)
    {
        if (strcmp(m->returnType, returnType) == 0)
        {
            list<char*>::iterator it1 = m->argsType.begin();
            list<char*>::iterator it2 = argsType.begin();
            while (it1 != m->argsType.end() && it2 != argsType.end())
            {
                if (strcmp((*it1), (*it2)) != 0)
                    return false;
                ++it1;
                ++it2;
            }
            if (it1 != m->argsType.end() || it2 != argsType.end())
                return false;
            return true;
        }
    }
    return false;
}

/******** VariableNode methods ********/

VariableNode::VariableNode(char *n, char *t) : name(n), type(t) {}

