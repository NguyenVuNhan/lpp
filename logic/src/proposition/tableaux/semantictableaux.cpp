#include "semantictableaux.h"
#include "../../notation/negate.h"
#include "enum.h"

SemanticTableaux::SemanticTableaux(shared_ptr<Node> tree)
    : tableaux(make_shared<STNode>(tree))
{
    generateProof(tableaux);
}

SemanticTableaux::~SemanticTableaux()
{
}

bool SemanticTableaux::ExportProof(string title, string filenname)
{
    ofstream out(filenname, ios::out | ios::binary);
    if(out.is_open())
    {
        out << "graph " << title << " {\n";
        out << "\tnode [ fontname = \"Arial\" ]\n";
        tableaux->treeTraveler(out, -1);
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

void SemanticTableaux::generateProof(shared_ptr<STNode> root)
{
//    for(auto e : root->nodes)
//        cout << e->toString() << endl;
//    cout << endl;
    // set default rule to NAN (lowest piority) and rule location to 0
    list<shared_ptr<Node>>::iterator pos = root->nodes.begin();
    RULES rule = NN;

    // loop though all node in STNode to find the location of highest piority node
    for (auto it = root->nodes.begin(); it != root->nodes.end(); it++)
    {
        if((*it)->getSTRuleName() < rule && !(*it)->isRulesReturned)
        {
            pos = it;
            rule = (*it)->getSTRuleName();
            if (rule == 1)
                break;
        }
    }

    // check if there no available node that can apply rule
    if(rule != NN)
    {
        (*pos)->getSTNodeChild(root, distance(root->nodes.begin(), pos));
        if(root->left != nullptr)
        {
            generateProof(root->left);
        }
        if(root->right != nullptr)
        {
            generateProof(root->right);
        }
    }
    else
    {
        // Check for this brach closed or not
        if(tautology)
        {
            for(auto i = root->nodes.begin(); i != root->nodes.end(); ++i)
                for(auto j = i; ++j != root->nodes.end();)
                {
                    string i_str = (*i)->toString();
                    string j_str = (*j)->toString();
                    if((i_str == ('~' + j_str)) || (('~' + i_str) == j_str))
                            return;
                }
            tautology = false;
        }
    }
}
