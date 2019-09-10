#ifndef BIIMPLICATION_H
#define BIIMPLICATION_H

#include "node.h"

class BiImplicate : public Node
{
public:
    explicit BiImplicate(Node *left = nullptr, Node *right = nullptr);
    ~BiImplicate();

    // Node interface
public:
    bool getValue(string valList);
    RULES getSTRuleName(bool isNegation);
    Node *nandify(bool isNegation);
    void getSTNodeChild(STNode *root, long pos, bool isNegation);
};

#endif // BIIMPLICATION_H
