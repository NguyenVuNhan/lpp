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
    bool getValue(string valList) override;
    shared_ptr<Node> nandify(bool isNegation) override;
    RULES getSTRuleName(bool isNegation) override;
    void getSTNodeChild(shared_ptr<STNode> root, long pos, bool isNegation) override;
    shared_ptr<Node> cnfFilter(bool isNegation = false) override;
    shared_ptr<Node> cnfDistribution() override;
    shared_ptr<Node> copy() override;

private:
    shared_ptr<Node> getMultiOr();
};

#endif // OR_H
