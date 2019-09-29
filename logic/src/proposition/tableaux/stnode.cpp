#include "stnode.h"
#include "../../notation/node.h"
#include "../../notation/negate.h"

STNode::STNode(shared_ptr<Node> root)
{
    left = nullptr;
    right = nullptr;
    if(root == nullptr) return;

    nodes.push_back(make_shared<Negate>(root));

    static int _id = 0;
    id = _id++;
}

STNode::STNode(list<shared_ptr<Node> > &nodeList)
{
    left = nullptr;
    right = nullptr;
    nodes = copyList<Node>(nodeList);

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

    if(left == nullptr && right == nullptr)
    {
        out << "\tnode" << id << "[label=" << "\"" << this->toString() << "\"]\n";

//        int newId = _id++;
//        out << "\tnode" << id << " -- node" << newId << endl;
//        out << "\tnode" << newId << "[label=\" X \" fontcolor=\"#F3360D\" color=\"#F3360D\"]\n";
        return;
    }
    else
    {
        out << "\tnode" << id << "[label=" << "\"" << this->toString() << "\"]\n";
    }
    if(left != nullptr)
        left->treeTraveler(out, id);
    if(right != nullptr)
        right->treeTraveler(out, id);
}
