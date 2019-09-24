#include "forall.h"
#include "negate.h"
#include "variable.h"
#include "../utils.h"

ForAll::ForAll(Node *left, Node *right) :
    Node(left, right)
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

void ForAll::getSTNodeChild(STNode *root, long pos, bool isNegation)
{
    if(!isRulesReturned)
    {
        isRulesReturned = true;

        root->left = new STNode(root->nodes);
        if (!isNegation)
        {
            list<Node *> tmp_list_l;
            tmp_list_l.push_back(this->copy());

            for(string var : root->listVar)
            {
                Node *proposition = right->copy();
                proposition->setVariable(left->notation, var);
                tmp_list_l.push_back(proposition);
            }

            listReplaceAt(root->left->nodes, tmp_list_l, pos);
        }
        else
        {
            list<Node *> tmp_list_l;

            int i = 1;
            string newVar;
            do
            {
                newVar = left->notation;
                newVar += to_string(i++);
            }
            while(contains(root->listVar, newVar));

            Node *proposition = new Negate(right->copy());
            proposition->setVariable(left->notation, newVar);
            tmp_list_l.push_back(proposition);

            listReplaceAt(root->left->nodes, tmp_list_l, pos);
            root->left->listVar.push_back(newVar);
        }
    }
}

Node *ForAll::copy()
{
    return new ForAll(left->copy(), right->copy());
}
