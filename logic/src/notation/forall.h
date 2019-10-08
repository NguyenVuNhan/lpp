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
    string toString() override;
    RULES getSTRuleName(bool isNegation) override;
    void getSTNodeChild(shared_ptr<STNode> root, long pos, bool isNegation) override;
    shared_ptr<Node> copy() override;
};

#endif // FORALL_H
