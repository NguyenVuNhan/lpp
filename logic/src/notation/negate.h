#ifndef NEGATION_H
#define NEGATION_H

#include "node.h"

class Negate : public Node
{
public:
    explicit Negate(Node *left = nullptr, Node *right = nullptr);
    ~Negate() override;

    // Node interface
public:
    bool getValue(string valList) override;
    Node *nandify(bool isNegation) override;
    string toString() override;
    RULES getSTRuleName(bool isNegation) override;
    void getSTNodeChild(STNode *root, long pos, bool isNegation) override;
    Node *copy() override;
    Node *cnfFilter(bool isNegation = false) override;
};

#endif // NEGATION_H
