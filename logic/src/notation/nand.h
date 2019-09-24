#ifndef NAND_H
#define NAND_H

#include "node.h"

class NAnd : public Node
{
public:
    explicit NAnd(Node *left = nullptr, Node *right = nullptr);
    ~NAnd() override;

    // Node interface
public:
    bool getValue(string valList) override;
    Node *nandify(bool isNegation) override;
    RULES getSTRuleName(bool isNegation) override;
    void getSTNodeChild(STNode *root, long pos, bool isNegation) override;
    Node *copy() override;
    Node *cnfFilter(bool isNegation = false) override;
};

#endif // NAND_H
