#ifndef STATEMENT_H
#define STATEMENT_H

#include "node.h"

class Statement : public Node
{
public:
    Statement(string notate, list<shared_ptr<Node> > listNodes);
    Statement(char notate, list<shared_ptr<Node> > listNodes);
    ~Statement() override;

    // Node interface
public:
    //! @copydoc Node::toString()
    string toString() override;
    //! @copydoc Node::getValue(string,string)
    void setVariable(string fromVariable, string toVariable) override;
    //! @copydoc Node::copy()
    shared_ptr<Node> copy() override;
    //! @copydoc Node::containedSpecialNode()
    bool containedSpecialNode() override;
};

#endif // STATEMENT_H
