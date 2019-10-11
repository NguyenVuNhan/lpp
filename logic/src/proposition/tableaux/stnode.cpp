#include "stnode.h"
#include "../../notation/node.h"
#include "../../notation/negate.h"

void STNode::copyList(list<shared_ptr<Node> > &other)
{
    for(auto e : other)
    {
        if(e->containedSpecialNode())
        {
            if(e->isRulesReturned)
            {
                shared_ptr<Node> tmp = e->copy();
                tmp->isRulesReturned = true;
                nodes.push_back(tmp);
            }
            else
            {
                nodes.push_back(e->copy());
            }
        }
        else
            nodes.push_back(e);
    }
}

STNode::STNode(shared_ptr<Node> root)
{
    left = nullptr;
    right = nullptr;
    if(root == nullptr) return;

    if(root->containedSpecialNode())
        nodes.push_back(make_shared<Negate>(root->copy()));
    else
        nodes.push_back(make_shared<Negate>(root));

    static int _id = 0;
    id = _id++;
}

STNode::STNode(list<shared_ptr<Node> > &nodeList, list<string> otherListVar)
{
    left = nullptr;
    right = nullptr;
    copyList(nodeList);
    listVar = otherListVar;

    static int _id = 0;
    id = _id++;
}

STNode::~STNode()
{
    nodes.clear();
}

string STNode::toString()
{
    string returnString = "{ ";
    bool first = true;
    for (auto node : nodes)
    {
        if(!first)
            returnString += ", ";
        returnString += node->toString();
        first = false;
    }
    returnString += " }";

    if(listVar.size() > 0)
    {
        returnString += "[ ";
        for (auto var : listVar)
        {
            returnString += var + ' ';
        }
        returnString += "]";
    }

    return returnString;
}

void STNode::treeTraveler(ofstream &out, int rootId)
{
    if(rootId != -1)
        out << "\tnode" << rootId << " -- node" << id << endl;

    out << "\tnode" << id << "[label=" << "\"" << this->toString() << "\"]\n";
    if(left != nullptr)
        left->treeTraveler(out, id);
    if(right != nullptr)
        right->treeTraveler(out, id);
}

