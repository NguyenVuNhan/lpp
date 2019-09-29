#include "multior.h"

MultiOr::MultiOr(list<shared_ptr<Node> > listNodes) :
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

bool MultiOr::getValue(string valList)
{
    bool value = false;

    for(auto e : variables)
        value |= e->getValue(valList);

    return value;
}


MultiOrNorm::MultiOrNorm(list<shared_ptr<Node> > listNodes) :
    MultiOr(listNodes)
{

}

MultiOrNorm::~MultiOrNorm()
{

}

string MultiOrNorm::toString()
{
    string return_str;
    bool first = true;
    for(auto i : variables)
    {
        if(!first)
            return_str += '|';
        return_str += i->toString();
        first = false;
    }

    if(return_str.size() == 1)
        return return_str;
    else
        return '(' + return_str + ')';
}
