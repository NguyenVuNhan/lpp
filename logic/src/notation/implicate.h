#ifndef IMPLICATION_H
#define IMPLICATION_H

#include "node.h"

class Implicate : public Node
{
public:
    explicit Implicate(shared_ptr<Node> left = nullptr, shared_ptr<Node> right = nullptr);
    ~Implicate() override;

    // Node interface
public:
    //! @copydoc Node::getValue(string)
    bool getValue(string valList) override;
    //! @copydoc Node::nandify(bool)
    shared_ptr<Node> nandify(bool isNegation) override;
    //! @copydoc Node::getSTRuleName(bool)
    RULES getSTRuleName(bool isNegation) override;
    //! @copydoc Node::getSTNodeChild(shared_ptr<STNode>,long,bool)
    void getSTNodeChild(shared_ptr<STNode> root, long pos, bool isNegation) override;
    //! @copydoc Node::cnfFilter(bool)
    shared_ptr<Node> cnfFilter(bool isNegation = false) override;
    //! @copydoc Node::copy()
    shared_ptr<Node> copy() override;
};

#endif // IMPLICATION_H
