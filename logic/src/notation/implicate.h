#ifndef IMPLICATION_H
#define IMPLICATION_H

#include "node.h"

class Implicate : public Node
{
public:
    explicit Implicate(Node *left = nullptr, Node *right = nullptr);
    ~Implicate() override;

    // Node interface
public:
    bool getValue(string valList) override;
    Node *nandify(bool isNegation) override;
    RULES getSTRuleName(bool isNegation) override;
    void getSTNodeChild(STNode *root, long pos, bool isNegation) override;
    Node *copy() override;
    Node *cnfFilter(bool isNegation = false) override;
};

#endif // IMPLICATION_H
