#include <algorithm>
#include <iostream>
#include <fstream>

#include "tree.h"
#include "../utils.h"
// Include all notation
#include "../notation/and.h"
#include "../notation/biimplicate.h"
#include "../notation/implicate.h"
#include "../notation/nand.h"
#include "../notation/negate.h"
#include "../notation/or.h"
#include "../notation/value.h"
#include "../notation/variable.h"

Tree::Tree(string prop)
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

Tree::Tree(Node *tree)
    : tableaux(tree)
{
    this->tree = tree;
    prop_in = tree->toStringPrefix();
}

Tree::~Tree()
{
    std::cout << tree->toString();
    delete tree;
}

Node *Tree::getTree()
{
    return tree;
}

list<string> Tree::getListVariable()
{
    if(varList.size() == 0)
    {
        string prop = prop_in;
        prop.erase(remove_if(prop.begin(), prop_in.end(),
                                  [](char c)
                                  {
                                      return !(c >= 65 && c <= 90);
                                  }),
                      prop.end());
        while (prop != "")
        {
            string currentChar = prop.substr(0, 1);
            if(!contains(varList, string(currentChar)))
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

Node *Tree::getStatement(string prop, unsigned int &pos)
{
    Node *node = nullptr;

    if(prop[pos] >= 48 && prop.data()[pos] <= 57)
        node = new Value(prop.substr(pos, 1));
    else
        node = new Variable(prop.substr(pos, 1));

    pos++;
    return node;
}

Node *Tree::getNode(char notation)
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

    default:
        return nullptr;
    }
}

Node *Tree::parse(string prop, unsigned int &pos)
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
        node = this->getStatement(prop, pos);
    }

    return node;
}
