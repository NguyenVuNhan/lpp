#ifndef STNODE_H
#define STNODE_H

#include <iostream>
#include <fstream>
#include <list>
#include "../../utils.h"

using namespace std;

class Node;

class STNode
{

private:
    int id = -1;

public:
    shared_ptr<STNode> left = nullptr;
    shared_ptr<STNode> right = nullptr;
    list<string> listVar;
    list<shared_ptr<Node> > nodes;

    explicit STNode(shared_ptr<Node> root = nullptr);
    explicit STNode(list<shared_ptr<Node> > &nodeList);
    ~STNode();
    string toString();
    void treeTraveler(ofstream &out, int rootId = -1);
};

#endif // STNODE_H
