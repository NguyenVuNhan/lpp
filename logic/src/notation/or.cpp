#include "or.h"
#include "negate.h"
#include "and.h"
#include "nand.h"

Or::Or(shared_ptr<Node> left, shared_ptr<Node> right)
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

shared_ptr<Node> Or::nandify(bool isNegation)
{
    shared_ptr<Node> notLeft = make_shared<Negate>(left);
    shared_ptr<Node> notRight = make_shared<Negate>(right);

    shared_ptr<Node> ret = make_shared<NAnd>(notLeft->nandify(), notRight->nandify());

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

void Or::getSTNodeChild(shared_ptr<STNode> root, long pos, bool isNegation)
{
    root->left = make_shared<STNode>(root->nodes);
    if (!isNegation)
    {
        root->right = make_shared<STNode>(root->nodes);

        listReplaceAt(root->left->nodes, left, pos);
        listReplaceAt(root->right->nodes, right, pos);
    }
    else
    {
        list<shared_ptr<Node> > tmp_list;
        tmp_list.push_back(make_shared<Negate>(left));
        tmp_list.push_back(make_shared<Negate>(right));
        listReplaceAt(root->left->nodes, tmp_list, pos);
    }
}

shared_ptr<Node> Or::cnfFilter(bool isNegation)
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

shared_ptr<Node> Or::cnfDistribution()
{
    shared_ptr<Node> l = nullptr;
    shared_ptr<Node> r = nullptr;
    shared_ptr<Node> ret = nullptr;

    if(left->notation == "&")
    {
        l = make_shared<Or>(left->left, right);
        r = make_shared<Or>(left->right, right);
        ret = make_shared<And>(l, r);
    }
    else if(right->notation == "&")
    {
        l = make_shared<Or>(left, right->left);
        r = make_shared<Or>(left, right->right);
        ret = make_shared<And>(l, r);
    }
    else
    {
        shared_ptr<Node> multiOr = getMultiOr();
        if(multiOr != nullptr)
            return multiOr;

        left = left->cnfDistribution();
        right = right->cnfDistribution();
        ret = shared_from_this();
    }

    return ret->cnfDistribution();
}

shared_ptr<Node> Or::getMultiOr()
{
    string notationList = "&=>%|&&||";
    list<shared_ptr<Node> > listNodes;
    if(notationList.find(left->notation) == string::npos)
    {
        if(notationList.find(right->notation) == string::npos)
        {
            listNodes.push_back(left);
            listNodes.push_back(right);
            return make_shared<MultiOr>(listNodes);
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
            return make_shared<MultiOr>(listNodes);
        }
        else if(left->notation == "||")
        {
            left->variables.push_back(right);
            return left;
        }
    }

    return nullptr;
}
