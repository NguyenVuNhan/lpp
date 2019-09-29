#ifndef NAND_H
#define NAND_H

#include "node.h"

class NAnd : public Node
{
public:
    explicit NAnd(shared_ptr<Node> l = nullptr, shared_ptr<Node> r = nullptr);
    ~NAnd() override;

    // Node interface
public:
    bool getValue(string valList) override;
    shared_ptr<Node> nandify(bool isNegation) override;
    RULES getSTRuleName(bool isNegation) override;
    void getSTNodeChild(shared_ptr<STNode> root, long pos, bool isNegation) override;
    shared_ptr<Node> cnfFilter(bool isNegation = false) override;
};

#endif // NAND_H
