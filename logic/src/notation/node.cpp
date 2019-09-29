#include "node.h"
#include "../utils.h"
#include "nand.h"
#include "and.h"
#include "or.h"
#include "negate.h"
#include "value.h"

Node *Node::copy()
{
    return nullptr;
}

Node *Node::cnfFilter(bool isNegation)
{
    if(isNegation)
    {
        return new Negate(this->copy());
    }
    else
    {
        return this->copy();
    }
}

Node *Node::cnfDistribution()
{
    return this;
}

void Node::getLeaf(list<Node *> &listNode)
{
    if(right == nullptr)
        listNode.push_back(this);
    else
    {
        left->getLeaf(listNode);
        right->getLeaf(listNode);
        free(this);
    }
}

Node *Node::orSimplify(Node *l, Node *r)
{
    if(l->notation == "0" && r->notation == "0")
    {
        delete l;
        delete r;
        return new Value("0");
    }
    else if(l->notation == "1" || r->notation == "1")
    {
        delete l;
        delete r;
        return new Value("1");
    }
    else if(l->notation == "0")
    {
        delete l;
        return r;
    }
    else if(r->notation == "0")
    {
        delete r;
        return l;
    }
    return new Or(l, r);
}

Node *Node::andSimplify(Node *l, Node *r)
{

    if(l->notation == "0" || r->notation == "0")
    {
        delete l;
        delete r;
        return new Value("0");
    }
    else if(l->notation == "1" && r->notation == "1")
    {
        delete l;
        delete r;
        return new Value("1");
    }
    else if(l->notation == "1")
    {
        delete l;
        return r;
    }
    else if(r->notation == "1")
    {
        delete r;
        return l;
    }
    return new And(l, r);
}

Node::Node(Node *left, Node *right)
    : left(left)
    , right(right)
{

}

Node::~Node()
{
    variables.remove_if(deleteAll<Node>);
    variables.clear();
    if (left != nullptr) delete left;
    if (right != nullptr) delete right;
    left = nullptr;
    right = nullptr;
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
    return '(' + left->toString() + notation + right->toString()+ ')';
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
        return new NAnd(this->copy(), new Value("1"));
    else
        return this->copy();
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
