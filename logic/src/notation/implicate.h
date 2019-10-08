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
    bool getValue(string valList) override;
    shared_ptr<Node> nandify(bool isNegation) override;
    RULES getSTRuleName(bool isNegation) override;
    void getSTNodeChild(shared_ptr<STNode> root, long pos, bool isNegation) override;
    shared_ptr<Node> cnfFilter(bool isNegation = false) override;
    shared_ptr<Node> copy() override;
};

#endif // IMPLICATION_H
