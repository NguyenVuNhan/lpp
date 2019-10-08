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

shared_ptr<Node> Value::nandify(bool isNegation)
{
    return shared_from_this();
}

void Value::setVariable(string fromVariable, string toVariable)
{
    return;
}

shared_ptr<Node> Value::cnfFilter(bool isNegation)
{
    if(isNegation)
    {
        return make_shared<Value>(notation == "0" ? "1" : "0");
    }
    else
    {
        return make_shared<Value>(notation);
    }
}

shared_ptr<Node> Value::copy()
{
    return make_shared<Value>(notation);
}
