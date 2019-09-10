#include "negate.h"
#include "or.h"
#include "nand.h"
#include "value.h"
#include"../utils.h"

Or::Or(Node *left, Node *right)
    : Node(left, right)
{
    notation = '|';
}

Or::~Or()
{
}

bool Or::getValue(string valList)
{
    return left->getValue(valList) || right->getValue(valList);
}

Node *Or::nandify(bool isNegation)
{
    Node *notLeft = new Negate(left);
    Node *notRight = new Negate(right);

    Node *ret = new NAnd(notLeft->nandify(), notRight->nandify());
    free(notLeft);
    free(notRight);

    return ret;
}

RULES Or::getSTRuleName(bool isNegation)
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

void Or::getSTNodeChild(STNode *root, long pos, bool isNegation)
{
    root->left = new STNode(root->nodes);
    if (!isNegation)
    {
        root->right = new STNode(root->nodes);

        listReplaceAt(root->left->nodes, left, pos);
        listReplaceAt(root->right->nodes, right, pos);
    }
    else
    {
        list<Node *> tmp_list;
        tmp_list.push_back(new Negate(left));
        tmp_list.push_back(new Negate(right));
        listReplaceAt(root->left->nodes, tmp_list, pos);
    }
}
