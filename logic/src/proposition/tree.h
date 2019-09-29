#ifndef TREE_H
#define TREE_H

#include "../notation/node.h"
#include "tableaux/stnode.h"
#include "tableaux/semantictableaux.h"

class Tree
{
private:
    string proposition = "";
    SemanticTableaux tableaux;

protected:
    shared_ptr<Node> tree = nullptr;
    list<string> varList;
    string prop_in;
    virtual shared_ptr<Node> getStatement(string prop, unsigned int &pos);
    virtual shared_ptr<Node> getNode(char notation);
    virtual shared_ptr<Node> parse(string prop, unsigned int &pos);

public:
    explicit Tree(string prop="");
    explicit Tree(shared_ptr<Node> tree=nullptr);
    virtual ~Tree();
    
    shared_ptr<Node> getTree();
    list<string> getListVariable();
    string getProposition();
    bool isTautology();
    bool getValue(string valList);
    bool exportGraph(string title, string filenname);
    bool exportProof(string title, string filenname);
};

#endif // TREE_H
