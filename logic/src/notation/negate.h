#ifndef NEGATION_H
#define NEGATION_H

#include "node.h"

class Negate : public Node
{
public:
    explicit Negate(Node *left = nullptr, Node *right = nullptr);
    ~Negate();

    // Node interface
public:
    bool getValue(string valList);
    Node *nandify(bool isNegation);
    string toString();
    RULES getSTRuleName(bool isNegation);
    void getSTNodeChild(STNode *root, long pos, bool isNegation);
};

#endif // NEGATION_H
