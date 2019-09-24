#include "multior.h"

MultiOr::MultiOr(list<Node *> listNodes) :
    Node(nullptr, nullptr)
{
    notation = "||";
    variables = listNodes;
}

MultiOr::~MultiOr()
{

}

string MultiOr::toString()
{

    string return_str;
    for(auto i : variables)
    {
        if(i->notation == "~")
            return_str += char(i->left->notation[0] + 32);
        else
            return_str += i->notation;
    }
    return return_str;
}

Node *MultiOr::copy()
{
    list<Node *> tmplist;
    for(auto *e : variables)
        tmplist.push_back(e->copy());
    return new MultiOr(tmplist);
}
