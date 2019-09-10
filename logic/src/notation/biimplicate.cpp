#include "biimplicate.h"
#include "negate.h"
#include "nand.h"
#include "value.h"
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
    Node *ret = new NAnd(new NAnd(left->nandify(), right->nandify()),
                         new NAnd(notLeft->nandify(), notRight->nandify()));
//    free(notLeft);
//    free(notRight);
    return ret;
}

void BiImplicate::getSTNodeChild(STNode *root, long pos, bool isNegation)
{
    root->left = new STNode(root->nodes);
    root->right = new STNode(root->nodes);
    if (isNegation)
    {
        list<Node *> tmp_list_l;
        tmp_list_l.push_back(new Negate(left));
        tmp_list_l.push_back(right);
        listReplaceAt(root->left->nodes, tmp_list_l, pos);

        list<Node *> tmp_list_r;
        tmp_list_r.push_back(left);
        tmp_list_r.push_back(new Negate(right));
        listReplaceAt(root->right->nodes, tmp_list_r, pos);
    }
    else
    {
        list<Node *> tmp_list_l;
        tmp_list_l.push_back(left);
        tmp_list_l.push_back(right);
        listReplaceAt(root->left->nodes, tmp_list_l, pos);

        list<Node *> tmp_list_r;
        tmp_list_r.push_back(new Negate(left));
        tmp_list_r.push_back(new Negate(right));
        listReplaceAt(root->right->nodes, tmp_list_r, pos);
    }
}
