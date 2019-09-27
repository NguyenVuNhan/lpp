#ifndef MULTIOR_H
#define MULTIOR_H

#include "node.h"

class MultiOr : public Node
{
public:
    explicit MultiOr(list<Node *> listNodes = list<Node *>());
    ~MultiOr() override;

    // Node interface
public:
    string toString() override;
    Node *copy() override;
    bool getValue(string valList) override;
};

class MultiOrNorm : public MultiOr
{
public:
    explicit MultiOrNorm(list<Node *> listNodes = list<Node *>());
    ~MultiOrNorm() override;
public:
    string toString() override;
};

#endif // MULTIOR_H
