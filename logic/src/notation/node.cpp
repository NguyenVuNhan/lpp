#include "node.h"
#include "../utils.h"
#include "nand.h"
#include "and.h"
#include "or.h"
#include "negate.h"
#include "value.h"

shared_ptr<Node> Node::cnfFilter(bool isNegation)
{
    if(isNegation)
    {
        return make_shared<Negate>(shared_from_this());
    }
    else
    {
        return shared_from_this();
    }
}

shared_ptr<Node> Node::cnfDistribution()
{
    return shared_from_this();
}

void Node::getLeaf(list<shared_ptr<Node>> &listNode)
{
    if(left == nullptr && notation == "||")
    {
        listNode.push_back(shared_from_this());
    }
    else if(right == nullptr)
    {
        list<shared_ptr<Node>> tmpList;
        tmpList.push_back(shared_from_this());
        listNode.push_back(make_shared<MultiOr>(tmpList));
    }
    else
    {
        left->getLeaf(listNode);
        right->getLeaf(listNode);
    }
}

shared_ptr<Node> Node::copy()
{
    cout << notation << endl;
    return shared_from_this();
}

bool Node::containedSpecialNode()
{
    if(left != nullptr && left->containedSpecialNode())
    {
        return true;
    }
    else if(right != nullptr && right->containedSpecialNode())
    {
        return true;
    }
    return false;
}

shared_ptr<Node> Node::orSimplify(shared_ptr<Node> l, shared_ptr<Node> r)
{
    if(l->notation == "0" && r->notation == "0")
    {
        return make_shared<Value>("0");
    }
    else if(l->notation == "1" || r->notation == "1")
    {
        return make_shared<Value>("1");
    }
    else if(l->notation == "0")
    {
        return r;
    }
    else if(r->notation == "0")
    {
        return l;
    }
    return make_shared<Or>(l, r);
}

shared_ptr<Node> Node::andSimplify(shared_ptr<Node> l, shared_ptr<Node> r)
{

    if(l->notation == "0" || r->notation == "0")
    {
        return make_shared<Value>("0");
    }
    else if(l->notation == "1" && r->notation == "1")
    {
        return make_shared<Value>("1");
    }
    else if(l->notation == "1")
    {
        return r;
    }
    else if(r->notation == "1")
    {
        return l;
    }
    return make_shared<And>(l, r);
}

Node::Node(shared_ptr<Node> left, shared_ptr<Node> right)
    : left(left)
    , right(right)
{

}

Node::~Node()
{
    variables.clear();
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

shared_ptr<Node> Node::nandify(bool isNegation)
{
    if(isNegation)
        return make_shared<NAnd>(shared_from_this(), make_shared<Value>("1"));
    else
        return shared_from_this();
}

RULES Node::getSTRuleName(bool isNegation)
{
    return NN;
}

void Node::getSTNodeChild(shared_ptr<STNode> root, long pos, bool isNegation)
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
