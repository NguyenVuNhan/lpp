#ifndef PREDICATE_H
#define PREDICATE_H

#include "tree.h"

class Predicate : public Tree
{
public:
    Predicate(string prop="");
    Predicate(Node *tree=nullptr);
    ~Predicate();

protected:
    Node *getStatement(string prop, unsigned int &pos);
    Node *getNode(char notation);
    Node *parse(string prop, unsigned int &pos);

};

#endif // PREDICATE_H
