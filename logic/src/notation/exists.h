#ifndef EXISTS_H
#define EXISTS_H

#include "node.h"

class Exists : public Node
{
public:
    Exists(Node *left = nullptr, Node *right = nullptr);
    ~Exists() override;

    // Node interface
public:
    string toString() override;
    RULES getSTRuleName(bool isNegation) override;
    void getSTNodeChild(STNode *root, long pos, bool isNegation) override;
    Node *copy() override;
};

#endif // EXISTS_H
