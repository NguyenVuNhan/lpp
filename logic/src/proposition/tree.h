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
    Node *tree = nullptr;
    list<string> varList;
    string prop_in;
    virtual Node *getStatement(string prop, unsigned int &pos);
    virtual Node *getNode(char notation);
    virtual Node *parse(string prop, unsigned int &pos);

public:
    explicit Tree(string prop="");
    explicit Tree(Node *tree=nullptr);
    virtual ~Tree();
    
    Node *getTree();
    list<string> getListVariable();
    string getProposition();
    bool isTautology();
    bool getValue(string valList);
    bool exportGraph(string title, string filenname);
    bool exportProof(string title, string filenname);
};

#endif // TREE_H
