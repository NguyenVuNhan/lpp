#include "negate.h"
#include "or.h"
#include "nand.h"
#include "and.h"
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

        listReplaceAt(root->left->nodes, left->copy(), pos);
        listReplaceAt(root->right->nodes, right->copy(), pos);
    }
    else
    {
        list<Node *> tmp_list;
        tmp_list.push_back(new Negate(left->copy()));
        tmp_list.push_back(new Negate(right->copy()));
        listReplaceAt(root->left->nodes, tmp_list, pos);
    }
}

Node *Or::copy()
{
    return new Or(left->copy(), right->copy());
}

Node *Or::cnfFilter(bool isNegation)
{
    if(isNegation)
    {
        return andSimplify(left->cnfFilter(true), right->cnfFilter(true));
    }
    else
    {
        return orSimplify(left->cnfFilter(), right->cnfFilter());
    }
}

Node *Or::cnfDistribution()
{
    Node *l = nullptr;
    Node *r = nullptr;
    Node *ret = nullptr;

    if(left->notation == "&")
    {
        l = new Or(left->left, right);
        r = new Or(left->right, right->copy());
        free(left);
        ret = new And(l, r);
    }
    else if(right->notation == "&")
    {
        l = new Or(left, right->left);
        r = new Or(left->copy(), right->right);
        free(right);
        ret = new And(l, r);
    }
    else
    {
        Node *multiOr = getMultiOr();
        if(multiOr != nullptr)
            return multiOr;

        l = left->cnfDistribution();
        r = right->cnfDistribution();
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
        ret = this;
    }

    return ret->cnfDistribution();
}

Node *Or::getMultiOr()
{
    string notationList = "&=>%|&&||";
    list<Node *> listNodes;
    if(notationList.find(left->notation) == string::npos)
    {
        if(notationList.find(right->notation) == string::npos)
        {
            listNodes.push_back(left);
            listNodes.push_back(right);
            return new MultiOr(listNodes);
        }
        else if(right->notation == "||")
        {
            right->variables.push_back(left);
            return right;
        }
    }
    else if(notationList.find(right->notation) == string::npos)
    {
        if(notationList.find(left->notation) == string::npos)
        {
            listNodes.push_back(left);
            listNodes.push_back(right);
            return new MultiOr(listNodes);
        }
        else if(left->notation == "||")
        {
            left->variables.push_back(right);
            return left;
        }
    }

    return nullptr;
}
