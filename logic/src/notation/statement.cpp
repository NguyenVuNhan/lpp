#include "statement.h"

Statement::Statement(string notate, list<Node *> variables)
    : Node(nullptr, nullptr)
{
    this->variables = variables;
    notation = notate;
}

Statement::Statement(char notate, list<Node *> variables)
    : Node(nullptr, nullptr)
{
    this->variables = variables;
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
