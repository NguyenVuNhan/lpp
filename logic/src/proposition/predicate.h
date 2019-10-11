#ifndef PREDICATE_H
#define PREDICATE_H

#include "tree.h"

class Predicate : public Tree
{
public:
    Predicate(string prop="");
    Predicate(shared_ptr<Node> tree=nullptr);
    ~Predicate() override;

protected:
    shared_ptr<Node> getStatement(string prop, unsigned int &pos) override;
    shared_ptr<Node> getNode(char notation) override;
    shared_ptr<Node> parse(string prop, unsigned int &pos) override;
    list<string> getListVariable() override;
};

#endif // PREDICATE_H
