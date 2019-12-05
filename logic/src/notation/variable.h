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
    //! @copydoc Node::getValue(string)
    bool getValue(string valList) override;
    //! @copydoc Node::toString()
    string toString() override;
    //! @copydoc Node::setVariable(string,string)
    void setVariable(string fromVariable, string toVariable) override;
    //! @copydoc Node::copy()
    shared_ptr<Node> copy() override;
};

#endif // VARIABLE_H
