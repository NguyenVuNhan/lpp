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
    bool getValue(string valList) override;
    RULES getSTRuleName(bool isNegation) override;
    shared_ptr<Node> nandify(bool isNegation) override;
    void getSTNodeChild(shared_ptr<STNode> root, long pos, bool isNegation = false) override;
    shared_ptr<Node> cnfFilter(bool isNegation = false) override;
    shared_ptr<Node> cnfDistribution() override;
    shared_ptr<Node> copy() override;
};

#endif // AND_H
