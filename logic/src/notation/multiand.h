#ifndef MULTIAND_H
#define MULTIAND_H

#include "node.h"

class MultiAnd : public Node
{
public:
    explicit MultiAnd(list<Node *> listNodes = list<Node *>());
    ~MultiAnd();

    // Node interface
public:
    string toString();
    Node *copy();
};

#endif // MULTIAND_H
