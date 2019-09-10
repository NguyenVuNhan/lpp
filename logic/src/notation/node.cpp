#include "node.h"
#include "../utils.h"
#include "nand.h"
#include "value.h"

Node::Node(Node *left, Node *right)
    : left(left)
    , right(right)
{

}

Node::~Node()
{
    variables.remove_if(deleteAll<Node>);
    variables.clear();
    delete left;
    delete right;
}

void Node::treeTraveler(ofstream &out, int rootId)
{
    static int _id = 0;
    id = _id++;

    if(rootId != -1)
        out << "\tnode" << rootId << " -- node" << id << endl;

    out << "\tnode" << id << "[label=" << "\"" << notation << "\"]\n";

    if(left != nullptr)
        left->treeTraveler(out, id);
    if(right != nullptr)
        right->treeTraveler(out, id);

    for(auto const &variable : variables)
        variable->treeTraveler(out, id);
}

string Node::toStringPrefix()
{
    if(left == nullptr)
    {
        return notation;
    }
    else if(right == nullptr)
    {
        return notation + left->toString();
    }
    return notation + '(' + left->toString() + ',' + right->toString() + ')';
}

string Node::toString()
{
    return "(" + left->toString() + notation + right->toString()+ ')';
}

bool Node::getValue(string valList)
{
    if(valList == "")
        return false;
    return true;
}

Node *Node::nandify(bool isNegation)
{
    if(isNegation)
        return new NAnd(this, new Value("1"));
    else
        return this;
}

RULES Node::getSTRuleName(bool isNegation)
{
    return NN;
}

void Node::getSTNodeChild(STNode *root, long pos, bool isNegation)
{
    return;
}

void Node::setVariable(string fromVariable, string toVariable)
{
    if(left != nullptr)
        left->setVariable(fromVariable, toVariable);
    if(right != nullptr)
        right->setVariable(fromVariable, toVariable);
}
