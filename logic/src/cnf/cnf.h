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
    static bool isUseless(shared_ptr<Node> node);
    shared_ptr<Node> nodeToMultiAnd(shared_ptr<Node> node);
    shared_ptr<Node> generateCNF(shared_ptr<Node> originTree);
};

class CNF : protected I_CNF
{
public:
    CNF(shared_ptr<Node> tree);
    CNF(string prop="");
    ~CNF();

    shared_ptr<Node> getCNF();
    string getProposition();

private:
    string proposition = "";
    string prop_in = "";
    list<string> varList;
    shared_ptr<Node> tree = nullptr;
    shared_ptr<Node> parse(string prop);
    shared_ptr<Node> getMultiOr(string prop);
    string getDavidPutnam(shared_ptr<Node> tree, uint pos);
};

#endif // CNF_H
