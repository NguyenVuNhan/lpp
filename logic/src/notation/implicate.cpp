#include "implicate.h"
#include "negate.h"
#include "nand.h"
#include "value.h"
#include "and.h"
#include "or.h"
#include "../utils.h"

Implicate::Implicate(Node *left, Node *right)
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

Node *Implicate::nandify(bool isNegation)
{
    Node *notRight = new Negate(right);
    Node *ret = new NAnd(left->nandify(), notRight->nandify());
    free(notRight);
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

void Implicate::getSTNodeChild(STNode *root, long pos, bool isNegation)
{
    root->left = new  STNode(root->nodes);
    if (!isNegation)
    {
        root->right = new STNode(root->nodes);

        listReplaceAt(root->left->nodes, new Negate(left->copy()), pos);
        listReplaceAt(root->right->nodes, right->copy(), pos);
    }
    else
    {
        list<Node *> tmp_list;
        tmp_list.push_back(left->copy());
        tmp_list.push_back(new Negate(right->copy()));
        listReplaceAt(root->left->nodes, tmp_list, pos);
    }
}

Node *Implicate::copy()
{
    return new Implicate(left->copy(), right->copy());
}

Node *Implicate::cnfFilter(bool isNegation)
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
