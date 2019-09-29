#ifndef MULTIOR_H
#define MULTIOR_H

#include "node.h"

class MultiOr : public Node
{
public:
    explicit MultiOr(list<shared_ptr<Node> > listNodes = list<shared_ptr<Node> >());
    ~MultiOr() override;

    // Node interface
public:
    string toString() override;
    bool getValue(string valList) override;
};

class MultiOrNorm : public MultiOr
{
public:
    explicit MultiOrNorm(list<shared_ptr<Node> > listNodes = list<shared_ptr<Node> >());
    ~MultiOrNorm() override;
public:
    string toString() override;
};

#endif // MULTIOR_H
