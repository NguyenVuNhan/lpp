#ifndef VARIABLE_H
#define VARIABLE_H

#include "node.h"

class Variable : public Node
{
public:
    explicit Variable(string notate);
    explicit Variable(char notate);
    ~Variable();

    // Node interface
public:
    bool getValue(string valList);
    string toString();
    void setVariable(string fromVariable, string toVariable);
    shared_ptr<Node> copy();
};

#endif // VARIABLE_H
