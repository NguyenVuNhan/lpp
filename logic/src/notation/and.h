#ifndef AND_H
#define AND_H

#include "node.h"

class And : public Node
{
public:
    explicit And(Node *l = nullptr, Node *r = nullptr);
    ~And() override;

    // Node interface
public:
    bool getValue(string valList) override;
    RULES getSTRuleName(bool isNegation) override;
    Node *nandify(bool isNegation) override;
    void getSTNodeChild(STNode *root, long pos, bool isNegation) override;
    Node *copy() override;
    Node *cnfFilter(bool isNegation = false) override;
    Node *cnfDistribution() override;
};

#endif // AND_H
