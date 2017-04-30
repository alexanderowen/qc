/* Author: Alexander Owen
 *
 * The SymbolTable is used to keep track of variables during type checking. 
 *
 * */

#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <unordered_map>
#include <string>
#include <list>

#include "TypeTree.hpp"

using std::unordered_map;
using std::list;
using std::string;

/*** Classes defined in this file***/
class SymbolTable;
class Sym;
class VariableSym;
class MethodSym;

class SymbolTable
{
    public:
        SymbolTable *parent;
        unordered_map<string, VariableSym *> vMap;

        SymbolTable(SymbolTable *p);
       ~SymbolTable();

        VariableSym *lookupVariable(char *name);
        void addVariable(char *name, VariableSym *value);
        void removeVariable(VariableSym *);

        // Given a list of SymbolTables, return their intersection
        SymbolTable *intersection(list<SymbolTable*> sts, TypeTree *tt);
        // Remove the contents of st2 from st1
        SymbolTable *remove(SymbolTable *st1, SymbolTable *st2);
        // Merge the lower-level VariableSym of argument to 'this'
        void merge(SymbolTable *);
    private:
        VariableSym *lookupVariableNoParent(char *name);

};

class Sym{}; // Abstract Base Class

class VariableSym : public Sym
{
    public:
        char *id;
        char *type;
        VariableSym(char *, char *);
};

class MethodSym : public Sym
{
    public:
        char *id;
        list<VariableSym *> *args;
        char *returnType;
        MethodSym(char *, list<VariableSym *> *, char *);
};


#endif
