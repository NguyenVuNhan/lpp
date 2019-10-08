#include "statement.h"

Statement::Statement(string notate, list<shared_ptr<Node> > listNodes)
    : Node()
{
    variables = listNodes;
    notation = notate;
}

Statement::Statement(char notate, list<shared_ptr<Node> > listNodes)
    : Node()
{
    variables = listNodes;
    notation = string(&notate, 1);
}

Statement::~Statement()
{

}

string Statement::toString()
{
    string returnString = notation;

    for(auto const &variable : variables)
    {
        returnString += variable->notation;
    }
    return returnString;
}

void Statement::setVariable(string fromVariable, string toVariable)
{
    for(auto &variable : variables)
    {
        if(variable->notation == fromVariable)
        {
            variable->notation = toVariable;
            return;
        }
    }
}

shared_ptr<Node> Statement::copy()
{
    list<shared_ptr<Node> > tmplist;
    for(auto e : variables)
        tmplist.push_back(e->copy());
    return make_shared<Statement>(notation, tmplist);
}

bool Statement::containedSpecialNode()
{
    return true;
}
