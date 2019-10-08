#ifndef VARIABLE_H
#define VARIABLE_H

#include "node.h"

class Variable : public Node
{
public:
    explicit Variable(string notate);
    explicit Variable(char notate);
    ~Variable() override;

    // Node interface
public:
    bool getValue(string valList) override;
    string toString() override;
    void setVariable(string fromVariable, string toVariable) override;
    shared_ptr<Node> copy() override;
};

#endif // VARIABLE_H
