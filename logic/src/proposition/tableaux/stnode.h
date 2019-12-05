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
    void copyList(list<shared_ptr<Node>> &other);
public:
    shared_ptr<STNode> left;
    shared_ptr<STNode> right;
    list<string> listVar;
    list<shared_ptr<Node>> nodes;

    explicit STNode(shared_ptr<Node> root = nullptr);
    explicit STNode(list<shared_ptr<Node> > &nodeList, list<string> otherListVar = list<string>());
    ~STNode();
    /*!
     * \brief get list of nodes (string)
     * \return list of nodes (string)
     */
    string toString();
    /*!
     * \brief travel STNode tree and produce a graph
     * \param out File output stream
     * \param rootId Parrent Id, equal to -1 by default if there is no parent
     */
    void treeTraveler(ofstream &out, int rootId = -1);
};

#endif // STNODE_H
