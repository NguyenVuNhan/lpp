#include "and.h"
#include "negate.h"
#include "nand.h"
#include "value.h"
#include "or.h"

And::And(shared_ptr<Node> l, shared_ptr<Node> r)
    : Node(l, r)
{
    notation = '&';
}

And::~And()
{
}

bool And::getValue(string valList)
{
    return (left->getValue(valList) && right->getValue(valList));
}

RULES And::getSTRuleName(bool isNegation)
{
    if (isNegation)
        return BETA;
    else
        return ALPHA;
}

shared_ptr<Node> And::nandify(bool isNegation)
{
    shared_ptr<Node> ret;
    if(isNegation)
    {
        shared_ptr<Node> tmp = make_shared<NAnd>(left, right);
        ret = tmp->nandify();
    }
    else
    {
        shared_ptr<Node> tmp_1 = make_shared<NAnd>(left, right);
        shared_ptr<Node> tmp_2 = make_shared<NAnd>(tmp_1->nandify(), make_shared<Value>("1"));
        ret = tmp_2->nandify();
    }
    return ret;
}

void And::getSTNodeChild(shared_ptr<STNode> root, long pos, bool isNegation)
{
    root->left = make_shared<STNode>(root->nodes);
    if (isNegation)
    {
        root->right = make_shared<STNode>(root->nodes);

        listReplaceAt<Node>(root->left->nodes, make_shared<Negate>(left), pos);
        listReplaceAt<Node>(root->right->nodes, make_shared<Negate>(right), pos);
    }
    else
    {
        list<shared_ptr<Node>> tmp_list;
        tmp_list.push_back(left);
        tmp_list.push_back(right);
        listReplaceAt<Node>(root->left->nodes, tmp_list, pos);
    }
}

shared_ptr<Node> And::cnfFilter(bool isNegation)
{
    if(isNegation)
    {
        return orSimplify(left->cnfFilter(true), right->cnfFilter(true));
    }
    else
    {
        return andSimplify(left->cnfFilter(), right->cnfFilter());
    }
}

shared_ptr<Node> And::cnfDistribution()
{
    shared_ptr<Node> l = left->cnfDistribution();
    shared_ptr<Node> r = right->cnfDistribution();
    left = l;
    right = r;

    return shared_from_this();
}
