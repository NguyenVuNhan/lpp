#include "negate.h"
#include "nand.h"
#include "value.h"

Negate::Negate(shared_ptr<Node> l)
    : Node(l, nullptr)
{
    notation = '~';
}

Negate::~Negate()
{
}

bool Negate::getValue(string valList)
{
    return !left->getValue(valList);
}

shared_ptr<Node> Negate::nandify(bool isNegation)
{
    if(isNegation)
        return left->nandify(isNegation);
    else
    {
        shared_ptr<Node> tmp = make_shared<NAnd>(left, make_shared<Value>("1"));
        shared_ptr<Node> ret = tmp->nandify();
        return ret;
    }
}

string Negate::toString()
{
    return notation + left->toString();
}

RULES Negate::getSTRuleName(bool isNegation)
{
    if (isNegation)
    {
        return ALPHA;
    }
    else
    {
        return left->getSTRuleName(true);
    }
}

void Negate::getSTNodeChild(shared_ptr<STNode> root, long pos, bool isNegation)
{
    if (isNegation)
    {
        left->getSTNodeChild(root, pos);
    }
    else
    {
        left->getSTNodeChild(root, pos, true);
    }
}

shared_ptr<Node> Negate::cnfFilter(bool isNegation)
{
    if(isNegation)
    {
        return left->cnfFilter();
    }
    else
    {
        return left->cnfFilter(true);
    }
}

shared_ptr<Node> Negate::copy()
{
    return make_shared<Negate>(left->copy());
}
