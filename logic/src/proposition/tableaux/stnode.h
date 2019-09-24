#ifndef STNODE_H
#define STNODE_H

#include <iostream>
#include <fstream>
#include <list>

using namespace std;

class Node;

class STNode
{

private:
    int id = -1;

public:
    STNode *left = nullptr;
    STNode *right = nullptr;
    list<string> listVar;
    list<Node *> nodes;

    explicit STNode(Node *root = nullptr);
    explicit STNode(list<Node *> &nodeList);
    ~STNode();
    string toString();
    void treeTraveler(ofstream &out, int rootId = -1);
};

#endif // STNODE_H
