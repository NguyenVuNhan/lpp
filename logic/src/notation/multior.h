#ifndef MULTIOR_H
#define MULTIOR_H

#include "node.h"

class MultiOr : public Node
{
public:
    explicit MultiOr(list<shared_ptr<Node> > listNodes = list<shared_ptr<Node> >());
    explicit MultiOr(shared_ptr<Node> node);
    ~MultiOr() override;

    // Node interface
public:
    string toString() override;
    string toStringPrefix() override;
    bool getValue(string valList) override;
    shared_ptr<Node> copy() override;
};

class MultiOrNorm : public MultiOr
{
public:
    explicit MultiOrNorm(list<shared_ptr<Node> > listNodes = list<shared_ptr<Node> >());
    explicit MultiOrNorm(shared_ptr<Node> node = nullptr);
    ~MultiOrNorm() override;
public:
    string toString() override;
    shared_ptr<Node> copy() override;
};

#endif // MULTIOR_H
