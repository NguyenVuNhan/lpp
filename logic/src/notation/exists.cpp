#include "exists.h"
#include "negate.h"
#include "variable.h"

Exists::Exists(shared_ptr<Node> l, shared_ptr<Node> r) :
    Node(l, r)
{
    notation = '@';
}

Exists::~Exists()
{

}

string Exists::toString()
{
    return "(@" + left->toString() + ".(" + right->toString() + "))";
}

RULES Exists::getSTRuleName(bool isNegation)
{
    if (isNegation)
    {
        if(!isRulesReturned)
            return GAMMA;
        return NN;
    }
    else
    {
        return DELTA;
    }
}

void Exists::getSTNodeChild(shared_ptr<STNode> root, long pos, bool isNegation)
{
    root->left = make_shared<STNode>(root->nodes, root->listVar);
    if (isNegation)
    {
        if(!isRulesReturned)
        {
            list<shared_ptr<Node>> tmp_list_l;
            shared_ptr<Node> tmp = make_shared<Negate>(copy());
            tmp->isRulesReturned = true;
            tmp_list_l.push_back(tmp);

            for(string var : root->listVar)
            {
                shared_ptr<Node> proposition = right;
                if(right->containedSpecialNode())
                    proposition = make_shared<Negate>(right->copy());
                else
                    proposition =  make_shared<Negate>(right);
                proposition->setVariable(left->notation, var);
                tmp_list_l.push_back(proposition);
            }

            listReplaceAt<Node>(root->left->nodes, tmp_list_l, pos);
        }
    }
    else
    {
        list<shared_ptr<Node> > tmp_list_l;

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
            proposition = right->copy();
        else
            proposition = right;
        proposition->setVariable(left->notation, newVar);
        tmp_list_l.push_back(proposition);

        listReplaceAt<Node>(root->left->nodes, tmp_list_l, pos);
        root->left->listVar.push_back(newVar);
    }
}


shared_ptr<Node> Exists::copy()
{
    return make_shared<Exists>(left->copy(), right->copy());
}
