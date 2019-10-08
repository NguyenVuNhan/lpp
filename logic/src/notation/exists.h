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
    string toString() override;
    RULES getSTRuleName(bool isNegation) override;
    void getSTNodeChild(shared_ptr<STNode> root, long pos, bool isNegation) override;
    shared_ptr<Node> copy() override;
};

#endif // EXISTS_H
