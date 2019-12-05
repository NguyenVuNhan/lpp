#ifndef FORALL_H
#define FORALL_H

#include "node.h"

class ForAll : public Node
{
public:
    ForAll(shared_ptr<Node> l = nullptr, shared_ptr<Node> r = nullptr);
    ~ForAll() override;

    // Node interface
public:
    //! @copydoc Node::toString()
    string toString() override;
    //! @copydoc Node::getSTRuleName(bool)
    RULES getSTRuleName(bool isNegation) override;
    //! @copydoc Node::getSTNodeChild(shared_ptr<STNode>,long,bool)
    void getSTNodeChild(shared_ptr<STNode> root, long pos, bool isNegation) override;
    //! @copydoc Node::copy()
    shared_ptr<Node> copy() override;
};

#endif // FORALL_H
