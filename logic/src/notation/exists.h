#ifndef EXISTS_H
#define EXISTS_H

#include "node.h"

class Exists : public Node
{
public:
    Exists(shared_ptr<Node> l = nullptr, shared_ptr<Node> r = nullptr);
    ~Exists() override;

    // Node interface
public:
    //! @copydoc Node::getValue(string)
    string toString() override;
    //! @copydoc Node::getSTRuleName(bool)
    RULES getSTRuleName(bool isNegation) override;
    //! @copydoc Node::getSTNodeChild(shared_ptr<STNode>,long,bool)
    void getSTNodeChild(shared_ptr<STNode> root, long pos, bool isNegation) override;
    //! @copydoc Node::copy()
    shared_ptr<Node> copy() override;
};

#endif // EXISTS_H
