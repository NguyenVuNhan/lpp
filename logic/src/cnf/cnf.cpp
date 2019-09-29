#include <sstream>

#include "cnf.h"
#include "../utils.h"
#include "../notation/multior.h"
#include "../notation/negate.h"
#include "../notation/variable.h"

CNF::CNF(shared_ptr<Node> tree)
{
    tree = generateCNF(tree);
    tree = nodeToMultiAnd(tree);
}

CNF::CNF(string prop)
{
    if (prop == "")
        return;
    prop_in = prop;
    tree = parse(prop);
}

CNF::~CNF()
{
}

shared_ptr<Node> CNF::getCNF()
{
    return tree;
}

string CNF::getProposition()
{
    if(proposition == "")
        proposition = tree->toString();
    return proposition;
}

shared_ptr<Node> CNF::parse(string prop)
{
    shared_ptr<Node> node = make_shared<MultiAnd>();

    prop.erase(remove_if(prop.begin(), prop.end(),
                         [](char c)
                         {
                            return c == ' ' || c == '[' || c == ']';
                         }),
                         prop.end());
    stringstream ss(prop);
    string segment;

    while(getline(ss, segment, ','))
    {
       node->variables.push_back(getMultiOr(segment));
    }

    return node;
}

shared_ptr<Node> CNF::getMultiOr(string prop)
{
    shared_ptr<Node> node = make_shared<MultiOr>();

    for(char c : prop)
    {
        if('a' <= c && c <= 'z')
            node->variables.push_back(make_shared<Negate>(make_shared<Variable>(char(toupper(c)))));
        else
            node->variables.push_back(make_shared<Variable>(char(toupper(c))));
    }

    return node;
}

string CNF::getDavidPutnam(shared_ptr<Node> tree, uint pos)
{
    string variable = readList(varList, pos);
    tree->variables.remove_if(isUseless);

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

bool I_CNF::isUseless(shared_ptr<Node> node)
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

shared_ptr<Node> I_CNF::nodeToMultiAnd(shared_ptr<Node> node)
{
    list<shared_ptr<Node> > listNode;
    node->getLeaf(listNode);
    return make_shared<MultiAnd>(listNode);
}

shared_ptr<Node> I_CNF::generateCNF(shared_ptr<Node> originTree)
{
    // make_shared<filtered tree will be create as a copy of origin tree
    shared_ptr<Node> tree = originTree->cnfFilter();
    tree = tree->cnfDistribution();
    return tree;
}
