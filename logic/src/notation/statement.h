#ifndef STATEMENT_H
#define STATEMENT_H

#include "node.h"

class Statement : public Node
{
public:
    Statement(string notate, list<shared_ptr<Node> > listNodes);
    Statement(char notate, list<shared_ptr<Node> > listNodes);
    ~Statement() override;

    // Node interface
public:
    string toString() override;
    void setVariable(string fromVariable, string toVariable) override;
    shared_ptr<Node> copy() override;
    bool containedSpecialNode() override;
};

#endif // STATEMENT_H
