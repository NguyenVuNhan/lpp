#ifndef MULTIAND_H
#define MULTIAND_H

#include "node.h"

class MultiAnd : public Node
{
public:
    explicit MultiAnd(list<Node *> listNodes = list<Node *>());
    ~MultiAnd() override;

    // Node interface
public:
    virtual string toString() override;
    Node *copy() override;
    bool getValue(string valList) override;
};

class MultiAndNorm : public MultiAnd
{
public:
    explicit MultiAndNorm(list<Node *> listNodes = list<Node *>());
    ~MultiAndNorm() override;
public:
    string toString() override;
};

#endif // MULTIAND_H
