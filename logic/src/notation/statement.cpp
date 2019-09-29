#include "statement.h"

Statement::Statement(string notate, list<shared_ptr<Node> > listNodes)
    : Node(nullptr, nullptr)
{
    variables = listNodes;
    notation = notate;
}

Statement::Statement(char notate, list<shared_ptr<Node> > listNodes)
    : Node(nullptr, nullptr)
{
    variables = listNodes;
    notation = string(&notate, 1);
}

Statement::~Statement()
{

}

string Statement::toString()
{
    string returnString = notation + '(';

    bool first = true;
    for(auto const &variable : variables)
    {
        if (!first)
            returnString += ',';
        returnString += variable->notation;
        first = false;
    }

    returnString += ')';
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
        tmplist.push_back(e);
    return make_shared<Statement>(notation, tmplist);
}
