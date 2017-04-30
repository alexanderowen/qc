/* Author: Alexander Owen
 *
 * The TranslatorVisitor is a subtype of Visitor. Traverses the AST to 
 * produce C code to generate. 
 *
 * Separated from visitors.hpp because this is used during code generation, 
 * not type checking. 
 *
 * */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "util.hpp"
#include "visitors.hpp"
#include "TranslatorVisitor.hpp"


/**************
 * 
 * Helper functions for TranslatorVisitor.cpp
 *
 * ************/

void printLocalVariables(unordered_map<string, string> typeMap, SymbolTable *st, FILE *f, list<string> *printed = NULL)
{
    bool unique = true;
    for (unordered_map<string, VariableSym*>::iterator it = st->vMap.begin(); it != st->vMap.end(); ++it) 
    {
        auto q = typeMap.find((*it).second->type);
        if (q != typeMap.end())
        {
            if (printed != NULL) //check if local variable is already printed
            {
                for (list<string>::iterator iter = printed->begin(); iter != printed->end(); iter++)
                {
                    if (strcmp(iter->c_str(), (*it).first.c_str()) == 0)
                        unique = false;
                }
            }
            if (unique)
            {
                fprintf(f, "%s %s;\n", q->second.c_str(), (*it).first.c_str());
            }
        }
        unique = true;
    }
}


/**************
 *
 * Defining methods for TranslatorVisitor
 *
 * ************/

TranslatorVisitor::TranslatorVisitor(char *fn, TypeTree *_tt, SymbolTable *_st)
{
    f = fopen(fn, "w");    
    if (f == NULL)
    {
        fprintf(stderr, "Error opening %s in TranslatorVisitor constructor\n", fn);
        exit(1);
    }
    typeMap.insert({"Obj", "obj_Obj"});
    typeMap.insert({"Int", "obj_Int"});
    typeMap.insert({"String", "obj_String"});
    typeMap.insert({"Boolean", "obj_Boolean"});
    typeMap.insert({"Nothing", "obj_Nothing"});

    keywords.insert({"true", "lit_true"});
    keywords.insert({"false", "lit_false"});
    /*
    keywords.insert({"true", "lit_true->value"});
    keywords.insert({"false", "lit_false->value"});
    */

    tt = _tt;
    st = _st;
}

TranslatorVisitor::~TranslatorVisitor()
{
    //if (f != NULL)
      //  fclose(f);
}

void TranslatorVisitor::visitProgram(Program *p)
{
    fprintf(f, "#include \"Builtins.h\"\n");
    fprintf(f, "#include <stdlib.h>\n\n");
    for (list<Class *>::const_iterator it = p->classes->begin(); it != p->classes->end(); ++it)
    {
        (*it)->accept(this);
    }
    fprintf(f, "int main() {\n");
    printLocalVariables(typeMap, p->st, f);
    for (list<Statement *>::const_iterator it = p->statements->begin(); it != p->statements->end(); ++it)
    {
        fprintf(f, "\t");
        (*it)->accept(this);
        fprintf(f, ";\n");
    }
    fprintf(f, "\n}");
}

void TranslatorVisitor::visitClass(Class *c)
{
    classMethods.clear(); //refresh
    printed.clear(); //refresh
    c->clssig->accept(this);
    c->clsbdy->accept(this);
    fprintf(f, "struct class_%s_struct the_class_%s_struct = {\n", className, className);
    fprintf(f, "\t.constructor = new_%s,\n", className);
    for (unordered_map<string, string>::const_iterator it = classMethods.begin(); it != classMethods.end(); ++it)
    {
        fprintf(f, "\t.%s = %s,\n", it->first.c_str(), it->second.c_str());
    }


    fprintf(f, "\n};\n");

    fprintf(f, "class_%s the_class_%s = &the_class_%s_struct;\n", className, className, className);
    fprintf(f, "\n\n\n"); //for readablility
}

void TranslatorVisitor::visitClassSignature(ClassSignature *cs)
{
    className = cs->id;
    TypeNode *tn = tt->findType(cs->id);
    fprintf(f, "struct class_%s_struct;\n", cs->id);
    fprintf(f, "typedef struct class_%s_struct* class_%s;\n", cs->id, cs->id);
    fprintf(f, "typedef struct obj_%s_struct {\n", cs->id);
    fprintf(f, "\tclass_%s clazz;\n", cs->id);

    for (list<VariableNode*>::const_iterator it = tn->instanceVars.begin(); it != tn->instanceVars.end(); ++it)
    {
        string str = (*it)->type;
        auto v = typeMap.find(str);
        fprintf(f, "\t%s %s;\n", v->second.c_str(), (*it)->name);
    }

    fprintf(f, "\n} * obj_%s;\n", cs->id);

    char c[256];
    sprintf(c, "obj_%s", cs->id);
    typeMap.insert({cs->id, c}); 

    fprintf(f, "struct class_%s_struct the_class_%s_struct;\n", cs->id, cs->id);
    fprintf(f, "extern class_%s the_class_%s;\n", cs->id, cs->id);

    fprintf(f, "struct class_%s_struct {\n", cs->id);
    fprintf(f, "\tobj_%s (*constructor) (", cs->id); 
    int i = 0; //need to print out constructor args 
    for (list<FormalArg *>::const_iterator it = cs->fargs->begin(); it != cs->fargs->end(); ++it)
    {
        (*it)->accept(this);
        if (i+1 < cs->fargs->size())
        {
            fprintf(f, ", ");
            i++;
        }
    }

    fprintf(f, ");\n");

    printMethodSignatures(tn);    
    getMethodNames(tn); //set the instance variable 'methodNames'
    fprintf(f, "\n};\n\n");
    
    fprintf(f, "obj_%s new_%s(", cs->id, cs->id);
    i = 0; 
    for (list<FormalArg *>::const_iterator it = cs->fargs->begin(); it != cs->fargs->end(); ++it)
    {
        (*it)->accept(this);
        printed.push_back((*it)->id);
        if (i+1 < cs->fargs->size())
        {
            fprintf(f, ", ");
            i++;
        }
    }
    fprintf(f, ") {\n");
    //cs->exop->accept(this);

}

void TranslatorVisitor::printMethodSignatures(TypeNode *tn)
{
    list<char*> displayed;
    while (tn != NULL)
    {
        for (list<MethodNode*>::const_iterator it = tn->methods.begin(); it != tn->methods.end(); ++it)
        {
            MethodNode *m = (*it);
            if (withinList(&displayed, m->id)) // we've already printed it
            {
                continue;
            }
            displayed.push_back(m->id);
            auto ret = typeMap.find(m->returnType);
            auto methName = typeMap.find(tn->name);
            fprintf(f, "\t%s (*%s) (%s", ret->second.c_str(), m->id, methName->second.c_str());
            for (list<char*>::const_iterator it = m->argsType.begin(); it != m->argsType.end(); ++it)
            {
                auto arg = typeMap.find((*it));
                fprintf(f, ", %s", arg->second.c_str());
            }
            fprintf(f, ");\n");
        }
        tn = tn->parent;
    }
}
 
//Sets the 'classMethods' instance variable with the appropriate values
void TranslatorVisitor::getMethodNames(TypeNode *tn)
{
    while (tn != NULL)
    {
        for (list<MethodNode*>::const_iterator it = tn->methods.begin(); it != tn->methods.end(); ++it)
        {
            MethodNode *m = (*it);
            string key = m->id;
            char v[256];
            sprintf(v, "%s_method_%s", tn->name, m->id);
            string value = v;
            classMethods.insert({key, value});
        }
        tn = tn->parent;
    }
}

void TranslatorVisitor::visitClassBody(ClassBody *cb)
{
    printLocalVariables(typeMap, cb->st, f, &printed);
    fprintf(f, "\tobj_%s this = malloc(sizeof(struct obj_%s_struct));\n", className, className);
    fprintf(f, "\tthis->clazz = the_class_%s;\n", className);
    for (list<Statement *>::const_iterator it = cb->stmts->begin(); it != cb->stmts->end(); ++it)
    {
        fprintf(f, "\t");
        (*it)->accept(this);
        fprintf(f, "\n");
    }
    fprintf(f, "\treturn this;\n}\n"); 
    for (list<Method *>::const_iterator it = cb->meths->begin(); it != cb->meths->end(); ++it)
    {
        (*it)->accept(this);
    }
}

void TranslatorVisitor::visitFormalArg(FormalArg *fa)
{
    auto q = typeMap.find(fa->type);
    fprintf(f, "%s %s", q->second.c_str(), fa->id);
}

void TranslatorVisitor::visitMethod(Method *m)
{
    inMethod = true;
    methodPrinted.clear();
    m->ident->accept(this); // print return type first
    auto q = typeMap.find(className);
    fprintf(f, " %s_method_%s(%s this", className, m->id, q->second.c_str());

    for (list<FormalArg *>::const_iterator it = m->fargs->begin(); it != m->fargs->end(); ++it)
    {
        fprintf(f, ", ");
        (*it)->accept(this);
        methodPrinted.push_back((*it)->id);
    }
    fprintf(f, ") {\n");
    printLocalVariables(typeMap, m->st, f, &methodPrinted);
    for (list<Statement *>::const_iterator it = m->stmts->begin(); it != m->stmts->end(); ++it)
    {
        fprintf(f, "\t");
        (*it)->accept(this);
        fprintf(f, ";\n");
    }
    FalseIdentOption *fi = dynamic_cast<FalseIdentOption*>(m->ident);
    if (fi != NULL)
    {
        fprintf(f, "\t return nothing;");
    }
    /*
    TrueIdentOption *ti = dynamic_cast<TrueIdentOption*>(m->ident);
    if (ti != NULL)
    {
        if (strcmp(ti->id, (char*)"Nothing") == 0)
        {
            fprintf(f, "\t return nothing;");
        }
    }
    */
    fprintf(f, "\n}\n");
    inMethod = false;
}

void TranslatorVisitor::visitTrueIdentOption(TrueIdentOption *t)
{
    if (inMethod)
    {
        auto q = typeMap.find(t->id);
        fprintf(f, "%s", q->second.c_str());
    }
}

void TranslatorVisitor::visitFalseIdentOption(FalseIdentOption *t)
{
    if (inMethod)
    {
        fprintf(f, "obj_Nothing");
    }
}

void TranslatorVisitor::visitAssignmentStatement(AssignmentStatement *a)
{
    /* Declares the type of variable; moved to begining of if, method, while, etc
    string t = getType(a->rexpr);
    fprintf(stderr, "Found type :'%s'\n", t.c_str());
    auto v = typeMap.find(t);
    if (v != typeMap.end()) 
    {
        //TODO: Prints unnecessarily when the variable is already defined
        fprintf(f, "%s ", v->second.c_str());
    }
    a->lexpr->print(f);
    fprintf(f, ";\n");
    */
    a->lexpr->accept(this);
    fprintf(f, " = ");
    //a->ident->accept(this); //TODO: Don't ignore ident???


    a->rexpr->accept(this);
    fprintf(f, ";");
}

void TranslatorVisitor::visitReturnStatement(ReturnStatement *r)
{
    fprintf(f, "return ");
    r->rexpr->accept(this);
    fprintf(f, ";");
}

void TranslatorVisitor::visitIfClause(IfClause *i)
{
    fprintf(f, "if ((");
    i->rexpr->accept(this);
    fprintf(f, ")->value) {\n"); // may need to remove
    printLocalVariables(typeMap, i->st, f, &methodPrinted);
    /*
    for (unordered_map<string, VariableSym*>::iterator it = i->st->vMap.begin(); it != i->st->vMap.end(); ++it) 
    {
        //fprintf(f, "Variable in if: %s\n", (*it).first.c_str());
        auto q = typeMap.find((*it).second->type);
        if (q != typeMap.end())
        {
            fprintf(f, "%s %s;\n", q->second.c_str(), (*it).first.c_str());
        }
    }
    */
    for (list<Statement *>::const_iterator it = i->stmts->begin(); it != i->stmts->end(); ++it)
    {
        fprintf(f, "\t");
        (*it)->accept(this);
        fprintf(f, ";\n");
    }
    fprintf(f, "\n}\n");
}

void TranslatorVisitor::visitElifClause(ElifClause *e)
{
    fprintf(f, "else if (");
    e->rexpr->accept(this);
    fprintf(f, ") {\n");
    printLocalVariables(typeMap, e->st, f, &methodPrinted);
    for (list<Statement *>::const_iterator it = e->stmts->begin(); it != e->stmts->end(); ++it)
    {
        fprintf(f, "\t");
        (*it)->accept(this);
        fprintf(f, ";\n");
    }
    fprintf(f, "\n}\n");
}

void TranslatorVisitor::visitTrueElseOption(TrueElseOption *e)
{
    fprintf(f, "else {\n");
    printLocalVariables(typeMap, e->st, f, &methodPrinted);
    for (list<Statement *>::const_iterator it = e->stmts->begin(); it != e->stmts->end(); ++it)
    {
        fprintf(f, "\t");
        (*it)->accept(this);
        fprintf(f, ";\n");
    }
    fprintf(f, "\n}\n");
}

void TranslatorVisitor::visitWhileStatement(WhileStatement *w)
{
    fprintf(f, "while (");
    w->rexpr->accept(this);
    fprintf(f, "->value) {\n"); //since rexpr is of type boolean, must access value
    //printLocalVariables(typeMap, w->st, f); //no concept of scoping within while loops
    for (list<Statement *>::const_iterator it = w->stmts->begin(); it != w->stmts->end(); ++it)
    {
        (*it)->accept(this);
    }
    fprintf(f, "\n}\n");
}

void TranslatorVisitor::visitConstructorRExpr(ConstructorRExpr *c)
{
    fprintf(f, "new_%s(", c->id);
    //for (list<RExpr *>::const_iterator it = c->args->begin(); it != c->args->end(); ++it)
    for (list<RExpr *>::const_iterator it = c->args->begin(); it != c->args->end(); )
    {
        (*it)->accept(this);
        if (++it != c->args->end())
        {
            fprintf(f, ", ");
        }
    }
    fprintf(f, ")");
}

void TranslatorVisitor::visitIntNode(IntNode *i)
{
    fprintf(f, "int_literal(%d)", i->value);
}

void TranslatorVisitor::visitStringNode(StringNode *s)
{
    fprintf(f, "str_literal(%s)", s->id);
}

void TranslatorVisitor::visitNotNode(NotNode *n)
{
    fprintf(f, "!(");
    n->value->accept(this);
    fprintf(f, ")");
}

void TranslatorVisitor::visitBinaryOperatorNode(BinaryOperatorNode *b)
{
    //b->left->accept(this);
    //fprintf(f, "->clazz->");
    switch(b->operation) {
        case 0:
            b->left->accept(this);
            fprintf(f, "->clazz->");
            fprintf(f, "PLUS");
            break;
        case 1:
            b->left->accept(this);
            fprintf(f, "->clazz->");
            fprintf(f, "MINUS");
            break;
        case 2:
            b->left->accept(this);
            fprintf(f, "->clazz->");
            fprintf(f, "TIMES");
            break;
        case 3:
            b->left->accept(this);
            fprintf(f, "->clazz->");
            fprintf(f, "DIVIDE");
            break;
        case 4:
            b->left->accept(this);
            fprintf(f, "->clazz->");
            fprintf(f, "EQUALS");
            break;
        case 5:
            b->left->accept(this);
            fprintf(f, "->clazz->");
            fprintf(f, "ATMOST");
            break;
        case 6:
            b->left->accept(this);
            fprintf(f, "->clazz->");
            fprintf(f, "LESS");
            break;
        case 7:
            b->left->accept(this);
            fprintf(f, "->clazz->");
            fprintf(f, "ATLEAST");
            break;
        case 8:
            b->left->accept(this);
            fprintf(f, "->clazz->");
            fprintf(f, "MORE");
            break;
        case 9:
            //fprintf(f, "AND");
            //
            fprintf(f, "((");
            b->left->accept(this);
            fprintf(f, "->value) ? (");
            b->right->accept(this);
            fprintf(f, ") : lit_false)");
            return;
            break;
        case 10:
            //fprintf(f, "OR");
            //
            fprintf(f, "((");
            b->left->accept(this);
            fprintf(f, "->value ) ? lit_true : (");
            b->right->accept(this);
            fprintf(f, "))");
            return;
            break;
        default:
            break;
    }
    fprintf(f, "(");
    b->left->accept(this); // Just a way of visiting printing left again
    fprintf(f, ", ");
    b->right->accept(this);
    fprintf(f, ")");


}

void TranslatorVisitor::visitIdentNode(IdentNode *i)
{
    string str = i->id;
    auto q = keywords.find(str);
    if (q != keywords.end())
    {
        fprintf(f, "%s", q->second.c_str());
    } 
    /*  Moved to ObjectFieldLExpr, where it belongs
    else if (strcmp(i->id, (char*)"this") == 0)
    {
        fprintf(f, "thing->%s", i->id);
    }
    */
    else
    {
        fprintf(f, "%s", i->id);
    }
}

void TranslatorVisitor::visitObjectFieldLExpr(ObjectFieldLExpr *o)
{
    o->rexpr->accept(this);
    fprintf(f, "->%s", o->id); //TODO: Only correct within the constructor

}

void TranslatorVisitor::visitDotRExpr(DotRExpr *d) 
{
    d->rexpr->accept(this);
    fprintf(f, "->clazz->%s(", d->id);
    d->rexpr->accept(this); // Just a way to print out first argument of methods
    for (list<RExpr *>::const_iterator it = d->args->begin(); it != d->args->end(); ++it)
    {
        fprintf(f, ", ");
        (*it)->accept(this);
    }
    fprintf(f, ")");
}    


/*****************
 *
 * TranslatorVisitor private methods
 *
 * ***************/

IdentNode *TranslatorVisitor::isIdent(RExpr *r)
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

ObjectFieldLExpr *TranslatorVisitor::isOFL(RExpr *r)
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

char *TranslatorVisitor::getType(RExpr *r)
{
    char *type;
    type = r->type();
    if (strcmp(type, (char*)"-") != 0) //type covered because it's a literal or easy to identify
        return type;
/*
    IdentNode *ident = isIdent(r);
    if (ident != NULL) //type is in the variable information
    {
        if (strcmp(ident->id, (char*)"this") == 0)
        {
            return className;
        }
        VariableSym *v = st->lookupVariable(ident->id);
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
*/

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

void TranslatorVisitor::printRExpr(RExpr *r)
{
    IdentNode *ident = isIdent(r);
    if (ident != NULL) //type is in the variable information
    {
        /*
        if (strcmp(ident->id, (char*)"this") == 0)
        {
            return className;
        }
        VariableSym *v = st->lookupVariable(ident->id);
        return v->type;
        */
        fprintf(f, "%s", ident->id);
    }
     
}
