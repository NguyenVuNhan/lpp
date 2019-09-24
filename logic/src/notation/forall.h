#ifndef FORALL_H
#define FORALL_H

#include "node.h"

class ForAll : public Node
{
public:
    ForAll(Node *left = nullptr, Node *right = nullptr);
    ~ForAll() override;

    // Node interface
public:
    string toString() override;
    RULES getSTRuleName(bool isNegation) override;
    void getSTNodeChild(STNode *root, long pos, bool isNegation) override;
    Node *copy() override;
};

#endif // FORALL_H
