#include <algorithm>

#include "predicate.h"
// Include all notation
#include "../notation/and.h"
#include "../notation/biimplicate.h"
#include "../notation/exists.h"
#include "../notation/forall.h"
#include "../notation/implicate.h"
#include "../notation/nand.h"
#include "../notation/negate.h"
#include "../notation/or.h"
#include "../notation/value.h"
#include "../notation/variable.h"
#include "../notation/statement.h"

Predicate::Predicate(string prop)
    : Tree("")
{
    prop_in = prop;
    prop.erase(remove_if(prop.begin(), prop.end(),
                         [](char c)
                         {
                             return c == '(' || c == ' ' || c == ')' ||
                                     c == '\0' || c == '\t' || c == '\n' || c == ',';
                         }),
                         prop.end());
    unsigned int pos = 0;
    tree = this->parse(prop, pos);
}

Predicate::Predicate(Node *tree)
    : Tree(tree)
{
    prop_in = tree->toStringPrefix();
}

Predicate::~Predicate()
{
}

Node *Predicate::getStatement(string prop, unsigned int &pos)
{
    Node *node = nullptr;



    return node;
}

Node *Predicate::getNode(char notation)
{
    switch (notation)
    {
    case '~':
        return new Negate();

    case '>':
        return new Implicate();

    case '=':
        return new BiImplicate();

    case '&':
        return new And();

    case '|':
        return new Or();

    case '%':
        return new NAnd();

    case '!':
        return new ForAll();

    case '@':
        return new Exists();

    default:
        return nullptr;
    }
}

Node *Predicate::parse(string prop, unsigned int &pos)
{
    Node *node = this->getNode(prop[pos]);

    if(node != nullptr)
    {
        node->left = this->parse(prop, ++pos);
        if(node->notation != "~")
            node->right = this->parse(prop, pos);
    }
    else
    {
        int code = prop[pos];
        if(code >= 65 && code <= 90)
        {
            char statementNotate = prop.at(pos);
            pos++;

            list<Node *> tmpVars;
            do
            {
                tmpVars.push_back(new Variable(prop.at(pos)));
                pos++;

                code = prop[pos];
            }
            while(code >= 97 && code <= 122);

            node = new Statement(statementNotate, tmpVars);
        }
        else
        {
            node = new Variable(prop.at(pos));
            pos++;
        }
    }

    return node;
}
