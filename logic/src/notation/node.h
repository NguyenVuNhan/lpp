#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <array>
#include <memory>
#include "../proposition/tableaux/enum.h"
#include "../proposition/tableaux/stnode.h"

using namespace std;

class Node
{
private:
    int id = -1;

protected:
    bool isRulesReturned = false;
    Node *orSimplify(Node *l, Node *r);
    Node *andSimplify(Node *l, Node *r);

public:
    shared_ptr *left = nullptr;
    Node *right = nullptr;
    list<Node *> variables;
    string notation = "1";

    explicit Node(Node *left = nullptr, Node *right = nullptr);
    virtual ~Node();

    /**
     * @brief travel tree and produce a graph
     * @param out File output stream
     * @param rootId Parrent Id, equal to -1 by default if there is no parent
     */
    void treeTraveler(ofstream &out, int rootId = -1);
    string toStringPrefix();
    virtual string toString();
    virtual bool getValue(string valList);
    virtual Node *nandify(bool isNegation = false);
    virtual RULES getSTRuleName(bool isNegation = false);
    virtual void getSTNodeChild(STNode *root, long pos, bool isNegation = false);
    virtual void setVariable(string fromVariable, string toVariable);
    virtual Node *copy();
    virtual Node *cnfFilter(bool isNegation = false);
    virtual Node *cnfDistribution();
    virtual void getLeaf(list<Node *> &listNode);
};
#endif // NODE_H
