#ifndef CNF_H
#define CNF_H

#include "../notation/multiand.h"
#include "../proposition/tree.h"

struct Resolution
{
    list<string> resolution;
    list<string> subtituteSolution;
};

struct I_CNF
{
    Resolution resolution(list<string> nodes, char v);
    static bool isUseless(Node *node);
    Node *nodeToMultiAnd(Node *node);
    Node *generateCNF(Node *originTree);
};

class CNF : protected I_CNF
{
public:
    CNF(Node *tree);
    ~CNF();

    Node *getCNF();

private:
    Node *cnf = nullptr;
};

#endif // CNF_H
