#include "exists.h"
#include "negate.h"
#include "variable.h"
#include "../utils.h"

Exists::Exists(Node *left, Node *right) :
    Node(left, right)
{
    notation = '@';
}

Exists::~Exists()
{

}

string Exists::toString()
{
    return "(@" + left->toString() + '.' + right->toString() + ')';
}

RULES Exists::getSTRuleName(bool isNegation)
{
    if (isNegation)
    {
        return GAMMA;
    }
    else
    {
        return DELTA;
    }
}

void Exists::getSTNodeChild(STNode *root, long pos, bool isNegation)
{
    if(!isRulesReturned)
    {
        root->left = new STNode(root->nodes);
        if (isNegation)
        {
            list<Node *> tmp_list_l;
            tmp_list_l.push_back(this->copy());

            for(string var : root->listVar)
            {
                Node *proposition = new Negate(right->copy());
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

            Node *proposition = right->copy();
            proposition->setVariable(left->notation, newVar);
            tmp_list_l.push_back(proposition);

            listReplaceAt(root->left->nodes, tmp_list_l, pos);
            root->left->listVar.push_back(newVar);
        }

        isRulesReturned = true;
    }
}

Node *Exists::copy()
{
    return new Exists(left->copy(), right->copy());
}
