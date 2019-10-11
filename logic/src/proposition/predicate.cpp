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
                             return c == '(' || c == ' ' || c == ')'
                                     || c == ',' || c == '.';
                         }),
                         prop.end());
    unsigned int pos = 0;
    tree = this->parse(prop, pos);
}

Predicate::Predicate(shared_ptr<Node> tree)
    : Tree(tree)
{
    prop_in = tree->toStringPrefix();
}

Predicate::~Predicate()
{
}

shared_ptr<Node> Predicate::getStatement(string prop, unsigned int &pos)
{
    shared_ptr<Node> node = nullptr;



    return node;
}

shared_ptr<Node> Predicate::getNode(char notation)
{
    switch (notation)
    {
    case '~':
        return make_shared<Negate>();

    case '>':
        return make_shared<Implicate>();

    case '=':
        return make_shared<BiImplicate>();

    case '&':
        return make_shared<And>();

    case '|':
        return make_shared<Or>();

    case '%':
        return make_shared<NAnd>();

    case '!':
        return make_shared<ForAll>();

    case '@':
        return make_shared<Exists>();

    default:
        return nullptr;
    }
}

shared_ptr<Node> Predicate::parse(string prop, unsigned int &pos)
{
    shared_ptr<Node> node = this->getNode(prop[pos]);

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

            list<shared_ptr<Node> > tmpVars;
            do
            {
                tmpVars.push_back(make_shared<Variable>(prop.at(pos)));
                pos++;

                code = prop[pos];
            }
            while(code >= 97 && code <= 122);

            node = make_shared<Statement>(statementNotate, tmpVars);
        }
        else
        {
            node = make_shared<Variable>(prop.at(pos));
            pos++;
        }
    }

    return node;
}

list<string> Predicate::getListVariable()
{
    if(varList.size() == 0)
    {
        string prop = prop_in;
        for (uint i = 0; i < prop.size(); ++i) {
            if(!(prop[i] >= 'a' && prop[i] <= 'z')) prop.erase(i--, 1);
        }
        while (prop != "")
        {
            string currentChar = string(1, prop.at(0));
            if(!contains(varList, currentChar))
            {
                varList.push_back(currentChar);
            }
            prop.erase(0,1);
        }
        varList.sort();
    }
    return varList;
}
