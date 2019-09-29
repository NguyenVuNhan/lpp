#include "nand.h"
#include "and.h"
#include "negate.h"
#include "value.h"

NAnd::NAnd(shared_ptr<Node> l, shared_ptr<Node> r)
    : Node(l, r)
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

void NAnd::getSTNodeChild(shared_ptr<STNode> root, long pos, bool isNegation)
{
    root->left = make_shared<STNode>(root->nodes);
    if (!isNegation)
    {
        root->right = make_shared<STNode>(root->nodes);

        listReplaceAt<Node>(root->left->nodes, make_shared<Negate>(left), pos);
        listReplaceAt<Node>(root->right->nodes, make_shared<Negate>(right), pos);
    }
    else
    {
        list<shared_ptr<Node> > tmp_list;
        tmp_list.push_back(left);
        tmp_list.push_back(right);
        listReplaceAt<Node>(root->left->nodes, tmp_list, pos);
    }
}

shared_ptr<Node> NAnd::cnfFilter(bool isNegation)
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

shared_ptr<Node> NAnd::nandify(bool isNegation)
{
    shared_ptr<Node> ret;
    if(!isNegation)
    {
        ret = make_shared<NAnd>(left->nandify(), right->nandify());
    }
    else
    {
        shared_ptr<Node> tmpLeft = make_shared<And>(left, right);
        ret = tmpLeft->nandify();
    }

    switch(ret->left->notation.at(0))
    {
    case '0':
    {
        return make_shared<Value>("1");
     }
    case '1':
        switch(ret->right->notation.at(0))
        {
        case '0':
        {
            return make_shared<Value>("1");
        }
        case '1':
        {
            return make_shared<Value>("0");
        }
        }

    default:
        return ret;
    }
}
