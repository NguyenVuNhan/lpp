#ifndef OR_H
#define OR_H

#include "node.h"
#include "multior.h"

class Or : public Node
{
public:
    explicit Or(Node *left = nullptr, Node *right = nullptr);
    ~Or() override;

    // Node interface
public:
    bool getValue(string valList) override;
    Node *nandify(bool isNegation) override;
    RULES getSTRuleName(bool isNegation) override;
    void getSTNodeChild(STNode *root, long pos, bool isNegation) override;
    Node *copy() override;
    Node *cnfFilter(bool isNegation = false) override;
    Node *cnfDistribution() override;

private:
    Node *getMultiOr();
};

#endif // OR_H
