#ifndef VALUE_H
#define VALUE_H

#include "node.h"

class Value : public Node
{
public:
    explicit Value(string value);
    ~Value() override;

    // Node interface
public:
    //! @copydoc Node::getValue(string)
    bool getValue(string valList) override;
    //! @copydoc Node::toString()
    string toString() override;
    //! @copydoc Node::nandify(bool)
    shared_ptr<Node> nandify(bool isNegation) override;
    //! @copydoc Node::setVariable(string,string)
    void setVariable(string fromVariable, string toVariable) override;
    //! @copydoc Node::cnfFilter(bool)
    shared_ptr<Node> cnfFilter(bool isNegation = false) override;
    //! @copydoc Node::copy()
    shared_ptr<Node> copy() override;
};

#endif // VALUE_H
