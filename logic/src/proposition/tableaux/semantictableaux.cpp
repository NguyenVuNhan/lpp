#include "semantictableaux.h"
#include "../../notation/negate.h"
#include "enum.h"

SemanticTableaux::SemanticTableaux(Node *tree)
    : tableaux(STNode(tree))
{

}

bool SemanticTableaux::ExportProof(string title, string filenname)
{
    ofstream out(filenname, ios::out | ios::binary);
    if(out.is_open())
    {
        out << "graph " << title << " {\n";
        out << "\tnode [ fontname = \"Arial\" ]\n";
        tableaux.treeTraveler(out, -1);
        out << '}';
        out.close();
        return true;
    }
    return false;
}

bool SemanticTableaux::isTautology()
{
    return tautology;
}

void SemanticTableaux::generateProof(STNode *root)
{
    // set default rule to NAN (lowest piority) and rule location to 0
    list<Node *>::iterator pos = root->nodes.begin();
    RULES rule = NN;

    // loop though all node in STNode to find the location of highest piority node
    for (list<Node *>::iterator it = root->nodes.begin(), total = root->nodes.end();
         it != total; ++it)
    {
        if((*it)->getSTRuleName() < rule)
        {
            pos = it;
            rule = (*it)->getSTRuleName();
        }
    }

    // check if there no available node that can apply rule
    if(rule != NN)
    {
        (*pos)->getSTNodeChild(root, distance(root->nodes.begin(), pos));
    }
    else
    {
        // Check for this brach closed or not
        if(tautology)
        {
            for(auto i = root->nodes.begin(); i != root->nodes.end(); ++i)
                for(auto j = i; ++j != root->nodes.end();)
                    if(((*i)->toString() == ('~' + (*j)->toString())) ||
                            ((*j)->toString() == ('~' + (*i)->toString())))
                            return;
            tautology = false;
        }
        return;
    }
}
