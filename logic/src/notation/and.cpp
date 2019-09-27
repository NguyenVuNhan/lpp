#include "and.h"
#include "negate.h"
#include "nand.h"
#include "value.h"
#include "or.h"
#include"../utils.h"

And::And(Node *l, Node *r)
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

Node *And::nandify(bool isNegation)
{
    Node *ret;
    if(isNegation)
    {
        Node *tmp = new NAnd(left, right);
        ret = tmp->nandify();
        free(tmp);
    }
    else
    {
        Node *tmp_1 = new NAnd(left, right);
        Node *tmp_2 = new NAnd(tmp_1->nandify(), new Value("1"));
        ret = tmp_2->nandify();
        free(tmp_1);
        free(tmp_2);
    }
    return ret;
}

void And::getSTNodeChild(STNode *root, long pos, bool isNegation)
{
    root->left = new STNode(root->nodes);
    if (isNegation)
    {
        root->right = new STNode(root->nodes);

        listReplaceAt(root->left->nodes, new Negate(left->copy()), pos);
        listReplaceAt(root->right->nodes, new Negate(right->copy()), pos);
    }
    else
    {
        list<Node *> tmp_list;
        tmp_list.push_back(left->copy());
        tmp_list.push_back(right->copy());
        listReplaceAt(root->left->nodes, tmp_list, pos);
    }
}

Node *And::copy()
{
    return new And(left->copy(), right->copy());
}

Node *And::cnfFilter(bool isNegation)
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

Node *And::cnfDistribution()
{
    Node *l = left->cnfDistribution();
    Node *r = right->cnfDistribution();
    if(left->notation == "|")
    {
        free(left);
    }
    if(right->notation == "|")
    {
        free(right);
    }
    left = l;
    right = r;

    return this;
}
