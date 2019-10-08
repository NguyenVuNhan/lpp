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
    bool getValue(string valList) override;
    shared_ptr<Node> nandify(bool isNegation) override;
    string toString() override;
    RULES getSTRuleName(bool isNegation) override;
    void getSTNodeChild(shared_ptr<STNode> root, long pos, bool isNegation) override;
    shared_ptr<Node> cnfFilter(bool isNegation = false) override;
    shared_ptr<Node> copy() override;
};

#endif // NEGATION_H
