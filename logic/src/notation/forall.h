#ifndef FORALL_H
#define FORALL_H

#include "node.h"

class ForAll : public Node
{
public:
    ForAll(Node *left = nullptr, Node *right = nullptr);
    ~ForAll();

    // Node interface
public:
    string toString();
    RULES getSTRuleName(bool isNegation);
    void getSTNodeChild(STNode *root, long pos, bool isNegation);
};

#endif // FORALL_H
