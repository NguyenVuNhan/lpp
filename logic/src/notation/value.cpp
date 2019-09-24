#include "value.h"

Value::Value(string value)
    : Node(nullptr, nullptr)
{
    notation = value;
}

Value::~Value()
{

}

bool Value::getValue(string valList)
{
    return notation == "1" ? true : false;
}

string Value::toString()
{
    return notation;
}

Node *Value::nandify(bool isNegation)
{
    return this;
}

void Value::setVariable(string fromVariable, string toVariable)
{
    return;
}

Node *Value::copy()
{
    return new Value(notation);
}

Node *Value::cnfFilter(bool isNegation)
{
    if(isNegation)
    {
        return new Value(notation == "0" ? "1" : "0");
    }
    else
    {
        return new Value(notation);
    }
}
