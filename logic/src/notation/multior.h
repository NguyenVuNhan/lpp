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
    //! @copydoc Node::toString()
    string toString() override;
    //! @copydoc Node::toStringPrefix()
    string toStringPrefix() override;
    //! @copydoc Node::getValue(string)
    bool getValue(string valList) override;
    //! @copydoc Node::copy()
    shared_ptr<Node> copy() override;
};

class MultiOrNorm : public MultiOr
{
public:
    explicit MultiOrNorm(list<shared_ptr<Node> > listNodes = list<shared_ptr<Node> >());
    explicit MultiOrNorm(shared_ptr<Node> node = nullptr);
    ~MultiOrNorm() override;
public:
    //! @copydoc Node::toString()
    string toString() override;
    //! @copydoc Node::copy()
    shared_ptr<Node> copy() override;
};

#endif // MULTIOR_H
