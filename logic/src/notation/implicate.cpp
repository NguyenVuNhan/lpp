#include "implicate.h"
#include "negate.h"
#include "nand.h"

Implicate::Implicate(shared_ptr<Node> left, shared_ptr<Node> right)
    : Node(left, right)
{
    notation = '>';
}

Implicate::~Implicate()
{
}

bool Implicate::getValue(string valList)
{
    return !left->getValue(valList) | right->getValue(valList);
}

shared_ptr<Node> Implicate::nandify(bool isNegation)
{
    shared_ptr<Node> notRight = make_shared<Negate>(right);
    shared_ptr<Node> ret = make_shared<NAnd>(left->nandify(), notRight->nandify());
    return ret;
}

RULES Implicate::getSTRuleName(bool isNegation)
{
    if (!isNegation)
    {
        return BETA;
    }
    else
    {
        return ALPHA;
    }
}

void Implicate::getSTNodeChild(shared_ptr<STNode> root, long pos, bool isNegation)
{
    root->left = make_shared<STNode>(root->nodes);
    if (!isNegation)
    {
        root->right = make_shared<STNode>(root->nodes);

        listReplaceAt<Node>(root->left->nodes, make_shared<Negate>(left), pos);
        listReplaceAt<Node>(root->right->nodes, right, pos);
    }
    else
    {
        list<shared_ptr<Node> > tmp_list;
        tmp_list.push_back(left);
        tmp_list.push_back(make_shared<Negate>(right));
        listReplaceAt<Node>(root->left->nodes, tmp_list, pos);
    }
}

shared_ptr<Node> Implicate::cnfFilter(bool isNegation)
{
    if(isNegation)
    {
        return andSimplify(left->cnfFilter(), right->cnfFilter(true));
    }
    else
    {
        return orSimplify(left->cnfFilter(true), right->cnfFilter());
    }
}
