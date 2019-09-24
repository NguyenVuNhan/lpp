#include "and.h"
#include "or.h"
#include "nand.h"
#include "negate.h"
#include "value.h"
#include "../utils.h"

NAnd::NAnd(Node *left, Node *right)
    : Node(left, right)
{
    notation = '%';
}

NAnd::~NAnd()
{

}

RULES NAnd::getSTRuleName(bool isNegation)
{
    if (!isNegation)
        return BETA;
    else
        return ALPHA;
}

void NAnd::getSTNodeChild(STNode *root, long pos, bool isNegation)
{
    root->left = new STNode(root->nodes);
    if (!isNegation)
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

Node *NAnd::copy()
{
    return new NAnd(left->copy(), right->copy());
}

Node *NAnd::cnfFilter(bool isNegation)
{
    if(isNegation)
    {
        return andSimplify(left->cnfFilter(), right->cnfFilter());
    }
    else
    {
        return orSimplify(left->cnfFilter(true), right->cnfFilter(true));
    }
}

bool NAnd::getValue(string valList)
{
    return !(left->getValue(valList) && right->getValue(valList));
}

Node *NAnd::nandify(bool isNegation)
{
    Node *ret;
    if(!isNegation)
    {
        ret = new NAnd(left->nandify(), right->nandify());
    }
    else
    {
        Node *tmpLeft = new And(left, right);
        ret = tmpLeft->nandify();
        free(tmpLeft);
    }

    switch(ret->left->notation.at(0))
    {
    case '0':
    {
        free(ret);
        return new Value("1");
     }
    case '1':
        switch(ret->right->notation.at(0))
        {
        case '0':
        {
            free(ret);
            return new Value("1");
        }
        case '1':
        {
            free(ret);
            return new Value("0");
        }
        }

    default:
        return ret;
    }
}
