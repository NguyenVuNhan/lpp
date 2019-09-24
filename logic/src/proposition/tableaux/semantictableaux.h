#ifndef SEMANTICTABLEAUX_H
#define SEMANTICTABLEAUX_H

#include "stnode.h"
#include "../../notation/node.h"
#include <string>


class SemanticTableaux
{
public:
    explicit SemanticTableaux(Node *tree = nullptr);
    ~SemanticTableaux();
    bool ExportProof(string title, string filenname);
    bool isTautology();

private:
    bool tautology = true;
    STNode *tableaux;
    void generateProof(STNode *root);

};

#endif // SEMANTICTABLEAUX_H
