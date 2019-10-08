#ifndef CNF_H
#define CNF_H

#include "../notation/multiand.h"
#include "../proposition/tree.h"

struct Reso
{
    shared_ptr<Node> resolution = make_shared<MultiAnd>();
    shared_ptr<Node> subtituteSolution = make_shared<MultiAnd>();
};

struct Janus
{
    shared_ptr<Node> cnf = make_shared<MultiAnd>();
    string non_janus = "";
};

struct I_CNF
{
    string solveNonJanus(shared_ptr<Node> node, char v);
    Reso resolution(shared_ptr<Node> node, char v);
    static bool isUseless(shared_ptr<Node> node);
    shared_ptr<Node> nodeToMultiAnd(shared_ptr<Node> node);
    shared_ptr<Node> generateCNF(shared_ptr<Node> originTree);
protected:
    bool findJanus(shared_ptr<Node> node);
private:
    bool isContain(shared_ptr<Node> nodes, string v);
    shared_ptr<Node> mergeNode(shared_ptr<Node> node1, shared_ptr<Node> node2, string v, string not_v);
};

class CNF : protected I_CNF,
            public Tree
{
public:
    CNF(shared_ptr<Node> otherTree);
    CNF(string prop="");
    ~CNF() override;
    string getDavidPutnam();
    list<string> getListVariable() override;

private:
    shared_ptr<Node> parse(string prop);
    shared_ptr<Node> getMultiOr(string prop);
    void getDavidPutnam(shared_ptr<Node> tree, uint pos, string &result);
};

#endif // CNF_H
