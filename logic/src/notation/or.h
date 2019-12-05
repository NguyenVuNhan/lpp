#ifndef OR_H
#define OR_H

#include "node.h"
#include "multior.h"

class Or : public Node
{
public:
    explicit Or(shared_ptr<Node> left = nullptr, shared_ptr<Node> right = nullptr);
    ~Or() override;

    // Node interface
public:
    //! @copydoc Node::getValue(string)
    bool getValue(string valList) override;
    //! @copydoc Node::nandify(bool)
    shared_ptr<Node> nandify(bool isNegation) override;
    //! @copydoc Node::getSTRuleName(bool)
    RULES getSTRuleName(bool isNegation) override;
    //! @copydoc Node::getValue(shared_ptr<STNode>,long,bool)
    void getSTNodeChild(shared_ptr<STNode> root, long pos, bool isNegation) override;
    //! @copydoc Node::cnfFilter(bool)
    shared_ptr<Node> cnfFilter(bool isNegation = false) override;
    //! @copydoc Node::cnfDistribution()
    shared_ptr<Node> cnfDistribution() override;
    //! @copydoc Node::copy()
    shared_ptr<Node> copy() override;

private:
    shared_ptr<Node> getMultiOr();
};

#endif // OR_H
