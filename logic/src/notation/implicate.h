#ifndef IMPLICATION_H
#define IMPLICATION_H

#include "node.h"

class Implicate : public Node
{
public:
    explicit Implicate(Node *left = nullptr, Node *right = nullptr);
    ~Implicate();

    // Node interface
public:
    bool getValue(string valList);
    Node *nandify(bool isNegation);
    RULES getSTRuleName(bool isNegation);
    void getSTNodeChild(STNode *root, long pos, bool isNegation);
};

#endif // IMPLICATION_H
