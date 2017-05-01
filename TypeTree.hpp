/* Author: Alexander Owen
 *
 * TypeTree.hpp defines the type tree to be used by the Quack typechecker
 *
 * The TypeTree defines the class hierarchy of a Quack program
 * It is comprised of TypeNodes, which contains information about the 
 * methods and instance variables of the type.
 *
 * */
#ifndef TYPE_H
#define TYPE_H

#include <list>

using std::list;


/* Classes defined in this file */
class MethodNode;
class VariableNode;
class TypeNode;
class TypeTree;


/* Class definitions */

class TypeTree 
{
    private:
        TypeNode *root;

        char *OBJ;
        char *INT;
        char *STR;
        char *BOOL;
        char *NOTHING;
    public:
        TypeTree();
        ~TypeTree();

        bool addSubtype(TypeNode *sub, char *super);
        bool addSubtype(char *sub, char *super);
        bool addMethodToType(char *type, MethodNode *m);
        bool addVarToType(char *type, VariableNode *v);

        bool isSubtype(char *_t1, char *_t2);
        bool isSupertype(char *_t1, char *_t2);

        /* Find least common ancestor between two types */
        char *LCA(char *_t1, char *_t2);

        bool typeHasMethod(char *type, char* method); 

        char *getVarFromType(char *type, char *var);
        MethodNode *typeGetMethod(char *type, char *method);

        TypeNode *findType(char *name);
        TypeNode *search(TypeNode *root, char *name);
        void print();
        void print(TypeNode *t);
};

/* Specifies a node of the TypeTree that represents a class/type,
 * which includes information about its variables and methods
 *
 * Includes pointer to parent TypeNode that indicates subclass'ness
 * */
class TypeNode
{
    public:
        char *name;
        TypeNode *parent;
        list<TypeNode *>     children;
        list<MethodNode *>   methods;
        list<VariableNode *> instanceVars;

        TypeNode(char *n, TypeNode *p);
       ~TypeNode();

        void addChild(TypeNode *type);
        void addChild(char *type);
        void addMethod(MethodNode *m);
        void addInstanceVar(VariableNode *v, TypeTree *tt);

        bool hasDescendant(char *type);
        bool hasMethod(char *name);
        bool hasInstanceVar(char *name);

        MethodNode *getMethod(char *name);
        VariableNode *getInstanceVar(char *name);

        int equals(TypeNode *type);
        int equals(char *name);
        void print();
};

/* Specifies a component of a TypeNode that represents a method of a class/type
 * */
class MethodNode 
{                                                                                                      
    public:                                                                                            
        char *id;                                                                                      
        list<char *> argsType;
        char *returnType;

        MethodNode(char *, list<char *> , char *);                                              
       ~MethodNode();
        void print();
        bool equals(MethodNode *);
}; 

/* Specifies a component of a TypeNode that represents an instance variable of a class/type
 * */
class VariableNode
{
    public:
        char *name;
        char *type;

        VariableNode(char *n, char *t);
};

#endif 
