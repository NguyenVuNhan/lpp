#include "biimplicate.h"
#include "negate.h"
#include "nand.h"
#include "value.h"
#include "and.h"
#include "or.h"
#include "../utils.h"

BiImplicate::BiImplicate(Node *left, Node *right)
    : Node(left, right)
{
    notation = '=';
}

BiImplicate::~BiImplicate()
{
}

bool BiImplicate::getValue(string valList)
{
    return left->getValue(valList) == right->getValue(valList);
}

RULES BiImplicate::getSTRuleName(bool isNegation)
{
    return BETA;
}

Node *BiImplicate::nandify(bool isNegation)
{
    Node *notLeft = new Negate(left);
    Node *notRight = new Negate(right);
    Node *tmpLeft = new NAnd(left->nandify(), right->nandify());
    Node *tmpRight = new NAnd(notLeft->nandify(), notRight->nandify());
    Node *ret = new NAnd(tmpLeft,tmpRight);
    free(notLeft);
    free(notRight);
    return ret;
}

void BiImplicate::getSTNodeChild(STNode *root, long pos, bool isNegation)
{
    root->left = new STNode(root->nodes);
    root->right = new STNode(root->nodes);
    if (isNegation)
    {
        list<Node *> tmp_list_l;
        tmp_list_l.push_back(new Negate(left->copy()));
        tmp_list_l.push_back(right->copy());
        listReplaceAt(root->left->nodes, tmp_list_l, pos);

        list<Node *> tmp_list_r;
        tmp_list_r.push_back(left->copy());
        tmp_list_r.push_back(new Negate(right->copy()));
        listReplaceAt(root->right->nodes, tmp_list_r, pos);
    }
    else
    {
        list<Node *> tmp_list_l;
        tmp_list_l.push_back(left->copy());
        tmp_list_l.push_back(right->copy());
        listReplaceAt(root->left->nodes, tmp_list_l, pos);

        list<Node *> tmp_list_r;
        tmp_list_r.push_back(new Negate(left->copy()));
        tmp_list_r.push_back(new Negate(right->copy()));
        listReplaceAt(root->right->nodes, tmp_list_r, pos);
    }
}

Node *BiImplicate::copy()
{
    return new BiImplicate(left->copy(), right->copy());
}

Node *BiImplicate::cnfFilter(bool isNegation)
{
    if(isNegation)
    {
        return orSimplify(andSimplify(left->cnfFilter(), right->cnfFilter(true)),
                          andSimplify(left->cnfFilter(true), right->cnfFilter()));
    }
    else
    {
        return andSimplify(orSimplify(left->cnfFilter(true), right->cnfFilter()),
                           orSimplify(left->cnfFilter(), right->cnfFilter(true)));
    }
}
