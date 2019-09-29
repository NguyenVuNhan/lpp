#include "biimplicate.h"
#include "negate.h"
#include "nand.h"

BiImplicate::BiImplicate(shared_ptr<Node> l, shared_ptr<Node> r)
    : Node(l, r)
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

shared_ptr<Node> BiImplicate::nandify(bool isNegation)
{
    shared_ptr<Node> notLeft = make_shared<Negate>(left);
    shared_ptr<Node> notRight = make_shared<Negate>(right);
    shared_ptr<Node> tmpLeft = make_shared<NAnd>(left->nandify(), right->nandify());
    shared_ptr<Node> tmpRight = make_shared<NAnd>(notLeft->nandify(), notRight->nandify());
    shared_ptr<Node> ret = make_shared<NAnd>(tmpLeft,tmpRight);
    return ret;
}

void BiImplicate::getSTNodeChild(shared_ptr<STNode> root, long pos, bool isNegation)
{
    root->left = make_shared<STNode>(root->nodes);
    root->right = make_shared<STNode>(root->nodes);
    if (isNegation)
    {
        list<shared_ptr<Node>> tmp_list_l;
        tmp_list_l.push_back(make_shared<Negate>(left));
        tmp_list_l.push_back(right);
        listReplaceAt<Node>(root->left->nodes, tmp_list_l, pos);

        list<shared_ptr<Node>> tmp_list_r;
        tmp_list_r.push_back(left);
        tmp_list_r.push_back(make_shared<Negate>(right));
        listReplaceAt<Node>(root->right->nodes, tmp_list_r, pos);
    }
    else
    {
        list<shared_ptr<Node>> tmp_list_l;
        tmp_list_l.push_back(left);
        tmp_list_l.push_back(right);
        listReplaceAt<Node>(root->left->nodes, tmp_list_l, pos);

        list<shared_ptr<Node>> tmp_list_r;
        tmp_list_r.push_back(make_shared<Negate>(left));
        tmp_list_r.push_back(make_shared<Negate>(right));
        listReplaceAt<Node>(root->right->nodes, tmp_list_r, pos);
    }
}

shared_ptr<Node> BiImplicate::cnfFilter(bool isNegation)
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
