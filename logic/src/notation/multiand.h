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
    //! @copydoc Node::toString()
    virtual string toString() override;
    //! @copydoc Node::toStringPrefix()
    string toStringPrefix() override;
    //! @copydoc Node::getValue(string)
    bool getValue(string valList) override;
    //! @copydoc Node::copy()
    shared_ptr<Node> copy() override;
};

class MultiAndNorm : public MultiAnd
{
public:
    explicit MultiAndNorm(list<shared_ptr<Node> > listNodes = list<shared_ptr<Node> >());
    ~MultiAndNorm() override;
public:
    //! @copydoc Node::toString()
    string toString() override;
    //! @copydoc Node::copy()
    shared_ptr<Node> copy() override;
};

#endif // MULTIAND_H
