#include "and.h"
#include "negate.h"
#include "nand.h"
#include "value.h"
#include"../utils.h"

And::And(Node *left, Node *right)
    : Node(left, right)
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

        listReplaceAt(root->left->nodes, new Negate(left), pos);
        listReplaceAt(root->right->nodes, new Negate(right), pos);
    }
    else
    {
        list<Node *> tmp_list;
        tmp_list.push_back(left);
        tmp_list.push_back(right);
        listReplaceAt(root->left->nodes, tmp_list, pos);
    }
}
