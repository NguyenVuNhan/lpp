#include <algorithm>
#include <iostream>
#include <fstream>

#include "tree.h"
#include "../utils.h"
// Include all notation
#include "../notation/and.h"
#include "../notation/biimplicate.h"
#include "../notation/implicate.h"
#include "../notation/multiand.h"
#include "../notation/multior.h"
#include "../notation/nand.h"
#include "../notation/negate.h"
#include "../notation/or.h"
#include "../notation/value.h"
#include "../notation/variable.h"

Tree::Tree(string prop)
{
    if (prop == "")
        return;

    prop_in = prop;
    prop.erase(remove_if(prop.begin(), prop.end(),
                         [](char c)
                         {
                             return c == '(' || c == ' ' || c == ')' || c == ',';
                         }),
                         prop.end());
    unsigned int pos = 0;
    tree = this->parse(prop, pos);
}

Tree::Tree(shared_ptr<Node> tree)
{
    if(tree != nullptr)
        this->tree = tree->copy();
    prop_in = tree->toStringPrefix();
}

Tree::~Tree()
{

}

shared_ptr<Node> Tree::getTree()
{
    return tree;
}

list<string> Tree::getListVariable()
{
    if(varList.size() == 0)
    {
        string prop = prop_in;
        for (uint i = 0; i < prop.size(); ++i) {
            if(prop[i] >= 'a' && prop[i] <= 'z')
            {
                prop[i] = char(toupper(prop[i]));
            }
            else if(!(prop[i] >= 'A' && prop[i] <= 'Z')) prop.erase(i--, 1);
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

string Tree::getProposition()
{
    if(proposition == "")
        proposition = tree->toString();
    return proposition;
}

bool Tree::getValue(string valList)
{
    return tree->getValue(valList);
}

bool Tree::isTautology()
{
    tableaux = SemanticTableaux(tree);
    return tableaux.isTautology();
}

bool Tree::exportGraph(string title, string filenname)
{
    ofstream out(filenname, ios::out | ios::binary);
    if(out.is_open())
    {
        out << "graph " << title << " {\n";
        out << "\tnode [ fontname = \"Arial\" ]\n";
        tree->treeTraveler(out, -1);
        out << '}';
        out.close();
        return true;
    }
    return false;
}

bool Tree::exportProof(string title, string filenname)
{
    return tableaux.ExportProof(title, filenname);
}

string Tree::getDavidPutnam()
{
    return "Can not use on this type of proposition";
}

shared_ptr<Node> Tree::getStatement(string prop, unsigned int &pos)
{
    shared_ptr<Node> node = nullptr;

    if(prop[pos] >= 48 && prop.data()[pos] <= 57)
        node = make_shared<Value>(prop.substr(pos, 1));
    else
        node = make_shared<Variable>(prop.substr(pos, 1));

    pos++;
    return node;
}

shared_ptr<Node> Tree::getNode(char notation)
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

    default:
        return nullptr;
    }
}

shared_ptr<Node> Tree::parse(string prop, unsigned int &pos)
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
        node = this->getStatement(prop, pos);
    }

    return node;
}
