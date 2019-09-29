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
    return "(!" + left->toString() + '.' + right->toString() + ')';
}

RULES ForAll::getSTRuleName(bool isNegation)
{
    if (!isNegation)
    {
        return GAMMA;
    }
    else
    {
        return DELTA;
    }
}

void ForAll::getSTNodeChild(shared_ptr<STNode> root, long pos, bool isNegation)
{
    if(!isRulesReturned)
    {
        isRulesReturned = true;

        root->left = make_shared<STNode>(root->nodes);
        if (!isNegation)
        {
            list<shared_ptr<Node> > tmp_list_l;
            tmp_list_l.push_back(shared_from_this());

            for(string var : root->listVar)
            {
                shared_ptr<Node> proposition = right;
                proposition->setVariable(left->notation, var);
                tmp_list_l.push_back(proposition);
            }

            listReplaceAt<Node>(root->left->nodes, tmp_list_l, pos);
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

            shared_ptr<Node> proposition = make_shared<Negate>(right);
            proposition->setVariable(left->notation, newVar);
            tmp_list_l.push_back(proposition);

            listReplaceAt<Node>(root->left->nodes, tmp_list_l, pos);
            root->left->listVar.push_back(newVar);
        }
    }
}
