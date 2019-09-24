#include "cnf.h"
#include "../utils.h"

CNF::CNF(Node *tree)
{
    cnf = generateCNF(tree);
    cnf = nodeToMultiAnd(cnf);
}

CNF::~CNF()
{
    delete cnf;
}

Node *CNF::getCNF()
{
    return cnf;
}

Resolution I_CNF::resolution(list<string> nodes, char v)
{
    Resolution reso;
    char v_upper = char(toupper(v));
    char v_lower = char(tolower(v));

    bool resolutionApplied = false;
    bool remove_i;
    for(auto i = nodes.begin(), end = nodes.end();
        i != end; ++i)
    {
        remove_i = false;
        for (auto j = next(i); j != end; ++j)
        {
            if(isContain(*i, v_upper))
            {
                if(isContain(*j, v_lower))
                {
                    remove((*i).begin(), (*i).end(), v_upper);
                    remove((*j).begin(), (*j).end(), v_lower);
                    reso.resolution.push_back(getUniqueString((*i)+(*j)));

                    resolutionApplied = true;
                    remove_i = true;
                    j = nodes.erase(j);
                }
            }
            else if(isContain(*i, v_lower))
            {
                if(isContain(*j, v_upper))
                {
                    remove((*i).begin(), (*i).end(), v_lower);
                    remove((*j).begin(), (*j).end(), v_upper);
                    reso.resolution.push_back(getUniqueString((*i)+(*j)));

                    resolutionApplied = true;
                    remove_i = true;
                    j = nodes.erase(j);
                }
            }
        }
        if(remove_i)
        {
            i = nodes.erase(i);
        }
    }
    reso.resolution.splice(reso.resolution.end(), nodes);


    if(resolutionApplied)
    {
        reso.subtituteSolution.push_back(string(1, v_lower));
    }
    return reso;
}

bool I_CNF::isUseless(Node *node)
{
    if(node->notation != "||") return false;

    string multiOrStr = node->toString();
    for(auto e : node->variables)
    {
        if(e->notation == "~"
                && multiOrStr.find(e->left->notation) != string::npos)
        {
            return true;
        }
        else if(multiOrStr.find(char(e->notation[0] + 32)) != string::npos)
        {
            return true;
        }
    }
    return false;
}

Node *I_CNF::nodeToMultiAnd(Node *node)
{
    list<Node *> listNode;
    node->getLeaf(listNode);
    return new MultiAnd(listNode);
}

Node *I_CNF::generateCNF(Node *originTree)
{
    // New filtered tree will be create as a copy of origin tree
    Node* tree = originTree->cnfFilter();
    tree = tree->cnfDistribution();
    return tree;
}
