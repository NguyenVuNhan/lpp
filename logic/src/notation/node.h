#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <fstream>
#include <string>
#include <array>

#include "../proposition/tableaux/enum.h"
#include "../proposition/tableaux/stnode.h"
#include "../utils.h"

using namespace std;

class Node : public enable_shared_from_this<Node>
{
private:
    int id = -1;

protected:
    shared_ptr<Node> orSimplify(shared_ptr<Node> l, shared_ptr<Node> r);
    shared_ptr<Node> andSimplify(shared_ptr<Node> l, shared_ptr<Node> r);

public:
    bool isRulesReturned = false;
    shared_ptr<Node> left = nullptr;
    shared_ptr<Node> right = nullptr;
    list<shared_ptr<Node>> variables;
    string notation = "1";

    explicit Node(shared_ptr<Node> left = nullptr, shared_ptr<Node> right = nullptr);
    virtual ~Node();

    /**
     * @brief travel tree and produce a graph
     * @param out File output stream
     * @param rootId Parrent Id, equal to -1 by default if there is no parent
     */
    void treeTraveler(ofstream &out, int rootId = -1);
    virtual string toStringPrefix();
    virtual string toString();
    virtual bool getValue(string valList);
    virtual shared_ptr<Node> nandify(bool isNegation = false);
    virtual RULES getSTRuleName(bool isNegation = false);
    virtual void getSTNodeChild(shared_ptr<STNode> root, long pos, bool isNegation = false);
    virtual void setVariable(string fromVariable, string toVariable);
    virtual shared_ptr<Node> cnfFilter(bool isNegation = false);
    virtual shared_ptr<Node> cnfDistribution();
    virtual void getLeaf(list<shared_ptr<Node>> &listNode);
    virtual shared_ptr<Node> copy();
    virtual bool containedSpecialNode();
};
#endif // NODE_H
