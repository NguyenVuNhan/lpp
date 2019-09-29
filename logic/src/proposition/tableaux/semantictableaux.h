#ifndef SEMANTICTABLEAUX_H
#define SEMANTICTABLEAUX_H

#include "stnode.h"
#include "../../notation/node.h"
#include <string>


class SemanticTableaux
{
public:
    explicit SemanticTableaux(shared_ptr<Node> tree = nullptr);
    ~SemanticTableaux();
    bool ExportProof(string title, string filenname);
    bool isTautology();

private:
    bool tautology = true;
    shared_ptr<STNode > tableaux;
    void generateProof(shared_ptr<STNode > root);

};

#endif // SEMANTICTABLEAUX_H
