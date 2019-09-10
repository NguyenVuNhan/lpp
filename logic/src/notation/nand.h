#ifndef NAND_H
#define NAND_H

#include "node.h"

class NAnd : public Node
{
public:
    explicit NAnd(Node *left = nullptr, Node *right = nullptr);
    ~NAnd();

    // Node interface
public:
    bool getValue(string valList);
    Node *nandify(bool isNegation);
    RULES getSTRuleName(bool isNegation);
    void getSTNodeChild(STNode *root, long pos, bool isNegation);
};

#endif // NAND_H
