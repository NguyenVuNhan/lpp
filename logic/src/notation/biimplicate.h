#ifndef BIIMPLICATION_H
#define BIIMPLICATION_H

#include "node.h"

class BiImplicate : public Node
{
public:
    explicit BiImplicate(shared_ptr<Node> l = nullptr, shared_ptr<Node> r = nullptr);
    ~BiImplicate() override;

    // Node interface
public:
    //! @copydoc Node::getValue(string)
    bool getValue(string valList) override;
    //! @copydoc Node::getSTRuleName(bool)
    RULES getSTRuleName(bool isNegation) override;
    //! @copydoc Node::nandify(bool)
    shared_ptr<Node> nandify(bool isNegation) override;
    //! @copydoc Node::getSTNodeChild(shared_ptr<STNode>,long,bool)
    void getSTNodeChild(shared_ptr<STNode> root, long pos, bool isNegation) override;
    //! @copydoc Node::cnfFilter(bool)
    shared_ptr<Node> cnfFilter(bool isNegation = false) override;
    //! @copydoc Node::copy()
    shared_ptr<Node> copy() override;
};

#endif // BIIMPLICATION_H
