#ifndef MULTIAND_H
#define MULTIAND_H

#include "node.h"

class MultiAnd : public Node
{
public:
    explicit MultiAnd(list<shared_ptr<Node> > listNodes = list<shared_ptr<Node> >());
    ~MultiAnd() override;

    // Node interface
public:
    virtual string toString() override;
    string toStringPrefix() override;
    bool getValue(string valList) override;
    shared_ptr<Node> copy() override;
};

class MultiAndNorm : public MultiAnd
{
public:
    explicit MultiAndNorm(list<shared_ptr<Node> > listNodes = list<shared_ptr<Node> >());
    ~MultiAndNorm() override;
public:
    string toString() override;
    shared_ptr<Node> copy() override;
};

#endif // MULTIAND_H
