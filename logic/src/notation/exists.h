#ifndef EXISTS_H
#define EXISTS_H

#include "node.h"

class Exists : public Node
{
public:
    Exists(Node *left = nullptr, Node *right = nullptr);
    ~Exists();

    // Node interface
public:
    string toString();
    RULES getSTRuleName(bool isNegation);
    void getSTNodeChild(STNode *root, long pos, bool isNegation);
};

#endif // EXISTS_H
