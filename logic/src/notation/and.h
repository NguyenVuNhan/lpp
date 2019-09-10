#ifndef AND_H
#define AND_H

#include "node.h"

class And : public Node
{
public:
    explicit And(Node *left = nullptr, Node *right = nullptr);
    ~And();

    // Node interface
public:
    bool getValue(string valList);
    RULES getSTRuleName(bool isNegation);
    Node *nandify(bool isNegation);
    void getSTNodeChild(STNode *root, long pos, bool isNegation);
};

#endif // AND_H
