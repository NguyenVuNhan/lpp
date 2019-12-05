#ifndef NEGATION_H
#define NEGATION_H

#include "node.h"

class Negate : public Node
{
public:
    explicit Negate(shared_ptr<Node> l = nullptr);
    ~Negate() override;

    // Node interface
public:
    //! @copydoc Node::getValue(string)
    bool getValue(string valList) override;
    //! @copydoc Node::nandify(bool)
    shared_ptr<Node> nandify(bool isNegation) override;
    //! @copydoc Node::toString()
    string toString() override;
    //! @copydoc Node::getSTRuleName(bool)
    RULES getSTRuleName(bool isNegation) override;
    //! @copydoc Node::getSTNodeChild(shared_ptr<STNode>,long,bool)
    void getSTNodeChild(shared_ptr<STNode> root, long pos, bool isNegation) override;
    //! @copydoc Node::cnfFilter(bool)
    shared_ptr<Node> cnfFilter(bool isNegation = false) override;
    //! @copydoc Node::copy()
    shared_ptr<Node> copy() override;
};

#endif // NEGATION_H
