#include "variable.h"
#include "nand.h"
#include "value.h"

Variable::Variable(string notate)
    : Node(nullptr, nullptr)
{
    notation = notate;
}

Variable::Variable(char notate)
    : Node(nullptr, nullptr)
{
    notation = string(&notate, 1);
}

Variable::~Variable()
{
}

bool Variable::getValue(string valList)
{
    return valList.at(valList.find(notation) + 1) == '1' ? true : false;
}

string Variable::toString()
{
    return notation;
}

void Variable::setVariable(string fromVariable, string toVariable)
{
    if(notation == fromVariable)
        notation = toVariable;
}

Node *Variable::copy()
{
    return new Variable(notation);
}
