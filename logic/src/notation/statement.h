#ifndef STATEMENT_H
#define STATEMENT_H

#include "node.h"

class Statement : public Node
{
public:
    Statement(string notate, list<shared_ptr<Node> > listNodes = list<shared_ptr<Node> >());
    Statement(char notate, list<shared_ptr<Node> > variables = list<shared_ptr<Node> >());
    ~Statement();

    // Node interface
public:
    string toString();
    void setVariable(string fromVariable, string toVariable);
    shared_ptr<Node> copy();
};

#endif // STATEMENT_H
