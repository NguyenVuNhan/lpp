#include "multiand.h"

MultiAnd::MultiAnd(list<shared_ptr<Node> > listNodes) :
    Node(nullptr, nullptr)
{
    notation = "&&";
    variables = listNodes;
}

MultiAnd::~MultiAnd()
{

}

string MultiAnd::toString()
{
    string return_str;
    bool first = true;
    for(auto i : variables)
    {
        if(!first)
            return_str += ", ";
        return_str += i->toString();
        first = false;
    }
    return "[ " + return_str + " ]";
}

string MultiAnd::toStringPrefix()
{
    return toString();
}

bool MultiAnd::getValue(string valList)
{
    bool value = true;

    for(auto e : variables)
        value &= e->getValue(valList);

    return value;
}

shared_ptr<Node> MultiAnd::copy()
{
    list<shared_ptr<Node> > tmplist;
    for(auto e : variables)
        tmplist.push_back(e->copy());
    return make_shared<MultiAnd>(tmplist);
}

MultiAndNorm::MultiAndNorm(list<shared_ptr<Node> > listNodes) :
    MultiAnd(listNodes)
{

}

MultiAndNorm::~MultiAndNorm()
{

}

string MultiAndNorm::toString()
{
    string return_str;
    bool first = true;
    for(auto i : variables)
    {
        if(!first)
            return_str += '&';
        return_str += i->toString();
        first = false;
    }

    if(return_str.size() == 1)
        return return_str;
    else
        return '(' + return_str + ')';
}

shared_ptr<Node> MultiAndNorm::copy()
{
    list<shared_ptr<Node> > tmplist;
    for(auto e : variables)
        tmplist.push_back(e->copy());
    return make_shared<MultiAndNorm>(tmplist);
}
