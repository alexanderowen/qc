/* Author: Alexander Owen
 *
 * The SymbolTable is used to keep track of variables during type checking. 
 *
 * */

#include <unordered_map>
#include <list>
#include <string>

#include <string.h>
#include "stdlib.h"
#include "stdio.h"

#include "SymbolTable.hpp"
#include "TypeTree.hpp"

using std::unordered_map;
using std::list;
using std::string;

VariableSym::VariableSym(char *i, char *t) : id(i), type(t) {}

MethodSym::MethodSym(char *i, list<VariableSym *> *a, char *r) : id(i), args(a), returnType(r) {}

SymbolTable::SymbolTable(SymbolTable *p) : parent(p) {}

SymbolTable::~SymbolTable()
{
    if (parent != NULL)
        delete parent;
    for (unordered_map<string, VariableSym*>::const_iterator key = vMap.begin(); key != vMap.end(); ++key)
    {
        delete key->second;        
    }

}

// note: this intersection does not travel all the way up the symboltable (ignores parent)
SymbolTable *SymbolTable::intersection(list<SymbolTable*> sts, TypeTree *tt)
{
    SymbolTable *total = new SymbolTable(parent);
    bool found = true;
    VariableSym *v;
    for (unordered_map<string, VariableSym*>::const_iterator key = vMap.begin(); key != vMap.end(); ++key)
    {
        char *type = key->second->type;
        for (list<SymbolTable*>::const_iterator it = sts.begin(); it != sts.end(); ++it)
        {
            v = (*it)->lookupVariableNoParent(strdup(key->first.c_str()));
            if (v == NULL)
            {
                found = false;
                break;
            } 
            else 
            {
                type = tt->LCA(type, v->type);
            } 
        }

        if (found) 
        {
            VariableSym *newVar = new VariableSym(strdup(key->first.c_str()),type);
            total->addVariable(strdup(key->first.c_str()), newVar);
        }
        found = true;
    }
    return total;    
}

void SymbolTable::merge(SymbolTable *_st)
{
    for (unordered_map<string, VariableSym*>::const_iterator key = _st->vMap.begin(); key != _st->vMap.end(); ++key)
    {
        VariableSym *v = this->lookupVariableNoParent((char*)key->first.c_str());
        if (v == NULL)
        {
            VariableSym *newVar = new VariableSym(strdup(key->first.c_str()), key->second->type);
            this->addVariable(strdup(key->first.c_str()), newVar);
        }
    }
}

SymbolTable *SymbolTable::remove(SymbolTable *st1, SymbolTable *st2)
{
    SymbolTable *total = new SymbolTable(st1->parent); //using st1 as the base
    for (unordered_map<string, VariableSym*>::iterator it = st1->vMap.begin(); it != st1->vMap.end(); ++it)
    {
        char *q = (char *) it->first.c_str();
        VariableSym *v = st2->lookupVariableNoParent(q);
        if (v == NULL)
        {
            total->addVariable(strdup(it->first.c_str()), it->second);
        }
    }
    return total;
}

VariableSym *SymbolTable::lookupVariable(char *name)
{
    string key = name;
    auto search = vMap.find(key);

    if (search != vMap.end())
    {
        return search->second;
    } 
    else if (parent != NULL) 
    {
        return parent->lookupVariable(name);    
    }
    else
    {
        return NULL;
    }
}
VariableSym *SymbolTable::lookupVariableNoParent(char *name)
{
    string key = name;
    auto search = vMap.find(key);

    if (search != vMap.end())
        return search->second;
    else
        return NULL;
}

void SymbolTable::addVariable(char *name, VariableSym *value)
{
    string key = name;
    vMap.insert({key, value});
}

void SymbolTable::removeVariable(VariableSym *vs)
{
    if (vs != NULL)
    {
        string key = vs->id;
        auto search = vMap.find(key);
        if (search != vMap.end())
        {
            vMap.erase(search);    
        }
    }
}
