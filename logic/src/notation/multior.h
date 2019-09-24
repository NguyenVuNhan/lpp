#ifndef MULTIOR_H
#define MULTIOR_H

#include "node.h"

class MultiOr : public Node
{
public:
    explicit MultiOr(list<Node *> listNodes = list<Node *>());
    ~MultiOr();

    // Node interface
public:
    string toString();
    Node *copy();
};

#endif // MULTIOR_H
