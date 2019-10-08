#ifndef PREDICATE_H
#define PREDICATE_H

#include "tree.h"

class Predicate : public Tree
{
public:
    Predicate(string prop="");
    Predicate(shared_ptr<Node> tree=nullptr);
    ~Predicate();

protected:
    shared_ptr<Node> getStatement(string prop, unsigned int &pos);
    shared_ptr<Node> getNode(char notation);
    shared_ptr<Node> parse(string prop, unsigned int &pos);
};

#endif // PREDICATE_H
