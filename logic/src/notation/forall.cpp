#include "forall.h"
#include "negate.h"
#include "variable.h"

ForAll::ForAll(shared_ptr<Node> l, shared_ptr<Node> r) :
    Node(l, r)
{
    notation = '!';
}

ForAll::~ForAll()
{

}

string ForAll::toString()
{
    return "(!" + left->toString() + ".(" + right->toString() + "))";
}

RULES ForAll::getSTRuleName(bool isNegation)
{
    if (isNegation)
    {
        return DELTA;
    }
    else
    {
        if(!isRulesReturned)
            return GAMMA;
        return NN;
    }
}

void ForAll::getSTNodeChild(shared_ptr<STNode> root, long pos, bool isNegation)
{
    root->left = make_shared<STNode>(root->nodes, root->listVar);
    if (isNegation)
    {
        int i = 1;
        string newVar;
        do
        {
            newVar = left->notation;
            newVar += to_string(i++);
        }
        while(contains(root->listVar, newVar));

        shared_ptr<Node> proposition;
        if(right->containedSpecialNode())
            proposition = make_shared<Negate>(right->copy());
        else
            proposition =  make_shared<Negate>(right);

        proposition->setVariable(left->notation, newVar);
        listReplaceAt<Node>(root->left->nodes, proposition, pos);
        root->left->listVar.push_back(newVar);
    }
    else
    {
        if(!isRulesReturned)
        {
            list<shared_ptr<Node> > tmp_list_l;
            shared_ptr<Node> tmp = copy();
            tmp->isRulesReturned = true;
            tmp_list_l.push_back(tmp);

            for(string var : root->listVar)
            {
                shared_ptr<Node> proposition = right;
                if(right->containedSpecialNode())
                    proposition = right->copy();
                else
                    proposition = right;
                proposition->setVariable(left->notation, var);
                tmp_list_l.push_back(proposition);
            }

            listReplaceAt<Node>(root->left->nodes, tmp_list_l, pos);
        }
    }
}


shared_ptr<Node> ForAll::copy()
{
    return make_shared<ForAll>(left->copy(), right->copy());
}
