#ifndef AND_H
#define AND_H

#include "node.h"

class And : public Node
{
public:
    explicit And(shared_ptr<Node> l = nullptr, shared_ptr<Node> r = nullptr);
    ~And() override;

    // Node interface
public:
    //! @copydoc Node::getValue(string)
    bool getValue(string valList) override;
    //! @copydoc Node::getSTRuleName(bool)
    RULES getSTRuleName(bool isNegation) override;
    //! @copydoc Node::nandify(bool)
    shared_ptr<Node> nandify(bool isNegation) override;
    //! @copydoc Node::getSTNodeChild(shared_ptr<STNode>,long,bool)
    void getSTNodeChild(shared_ptr<STNode> root, long pos, bool isNegation = false) override;
    //! @copydoc Node::cnfFilter(bool)
    shared_ptr<Node> cnfFilter(bool isNegation = false) override;
    //! @copydoc Node::cnfDistribution()
    shared_ptr<Node> cnfDistribution() override;
    //! @copydoc Node::copy()
    shared_ptr<Node> copy() override;
};

#endif // AND_H
