#ifndef BIIMPLICATION_H
#define BIIMPLICATION_H

#include "node.h"

class BiImplicate : public Node
{
public:
    explicit BiImplicate(Node *left = nullptr, Node *right = nullptr);
    ~BiImplicate() override;

    // Node interface
public:
    bool getValue(string valList) override;
    RULES getSTRuleName(bool isNegation) override;
    Node *nandify(bool isNegation) override;
    void getSTNodeChild(STNode *root, long pos, bool isNegation) override;
    Node *copy() override;
    Node *cnfFilter(bool isNegation = false) override;
};

#endif // BIIMPLICATION_H
