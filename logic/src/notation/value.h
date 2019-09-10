#ifndef VALUE_H
#define VALUE_H

#include "node.h"

class Value : public Node
{
public:
    explicit Value(string value);
    ~Value();

    // Node interface
public:
    bool getValue(string valList);
    string toString();
    Node *nandify(bool isNegation);
    void setVariable(string fromVariable, string toVariable);
};

#endif // VALUE_H
