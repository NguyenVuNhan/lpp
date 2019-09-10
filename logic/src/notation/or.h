#ifndef OR_H
#define OR_H

#include "node.h"

class Or : public Node
{
public:
    explicit Or(Node *left = nullptr, Node *right = nullptr);
    ~Or();

    // Node interface
public:
    bool getValue(string valList);
    Node *nandify(bool isNegation);
    RULES getSTRuleName(bool isNegation);
    void getSTNodeChild(STNode *root, long pos, bool isNegation);
};

#endif // OR_H
