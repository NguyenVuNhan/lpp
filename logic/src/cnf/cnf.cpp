#include <sstream>

#include "cnf.h"
#include "../utils.h"
#include "../notation/multior.h"
#include "../notation/negate.h"
#include "../notation/variable.h"

CNF::CNF(shared_ptr<Node> otherTree)
    : Tree(otherTree)
{
    if(otherTree->notation == "&&")
        return;
    tree = generateCNF(tree);
    tree = nodeToMultiAnd(tree);
}

CNF::CNF(string prop)
    : Tree("")
{
    if (prop == "")
        return;
    prop_in = prop;
    tree = parse(prop);
}

CNF::~CNF()
{
}

string CNF::getDavidPutnam()
{
    string result = "";
    getListVariable();
    getDavidPutnam(tree, 0, result);
    return result;
}

list<string> CNF::getListVariable()
{
    if(varList.size() == 0)
    {
        string prop = prop_in;
        for (uint i = 0; i < prop.size(); ++i) {
            if(prop[i] >= 'a' && prop[i] <= 'z')
            {
                prop[i] = char(toupper(prop[i]));
            }
            else if(!(prop[i] >= 'A' && prop[i] <= 'Z')) prop.erase(i--, 1);
        }
        while (prop != "")
        {
            string currentChar = string(1, prop.at(0));
            if(!contains(varList, currentChar))
            {
                varList.push_back(currentChar);
            }
            prop.erase(0,1);
        }
        varList.sort();
    }
    return varList;
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

void CNF::getDavidPutnam(shared_ptr<Node> cnf, uint pos, string &result)
{
    if(findJanus(cnf))
    {
        result = "UNSAT";
        INFO("Result = " + result)
        return;
    }
    //Pick next variable
    char v = readList(varList, pos).at(0);
    if(cnf->variables.size() == 0 && pos+1 < varList.size())
    {
        getDavidPutnam(cnf, pos+1, result);
        result = '1' + result;
        result = v + result;
        return;
    }
    INFO("Pick: " + string(1, v))
    // remove useless
    cnf->variables.remove_if(isUseless);
    INFO("Remove useless: " + cnf->toString())
    // solve non-janus
    string non_janus = solveNonJanus(cnf, v);
    INFO("Sole Non-Janus: " + non_janus + " " + cnf->toString())
    Reso reso = resolution(cnf, v);
    INFO("Resolution: " + reso.resolution->toString())
    if(pos+1 < varList.size())
    {
        getDavidPutnam(reso.resolution, pos+1, result);
    }
    if(result != "UNSAT")
    {
        if(non_janus != "")
        {
            result = non_janus + result;
        }
        else
        {
            INFO("Subtitude resolution: " + reso.subtituteSolution->toString())
            if(reso.subtituteSolution->variables.size() == 1)
            {
                non_janus = solveNonJanus(reso.subtituteSolution, v);
                INFO("Solve Non-Janus: " + non_janus + " " + reso.subtituteSolution->toString())
                if(non_janus != "")
                {
                    result = non_janus + result;
                }
            }
            else
            {
                result = '1' + result;
                INFO("Set: " + string(1, v) + string(1, result.at(0)))
                result = v + result;
            }
        }
    }
}

string I_CNF::solveNonJanus(shared_ptr<Node> node, char v)
{
    string non_janus = "";
    string node_str = node->toString();

    char _uv = char(toupper(v));
    char _lv = char(tolower(v));
    string _v = "";
    if(node_str.find(_uv) != string::npos && node_str.find(_lv) == string::npos)
    {
        _v += _uv;
        non_janus += _uv;
        non_janus += "1";
    }
    else if(node_str.find(_uv) == string::npos && node_str.find(_lv) != string::npos)
    {
        _v += _lv;
        non_janus += _uv;
        non_janus += "0";
    }

    if(non_janus != "")
    {
        node->variables.remove_if([_v](shared_ptr<Node> e)
                                  {
                                      return e->toString().find(_v) != string::npos;
                                  });
    }
    node->variables.sort([](const shared_ptr<Node> &node1, const shared_ptr<Node> &node2)
    {
        char node1_chr = node1->notation == "~" ? char(node1->left->notation[0] + 32) : node1->notation.at(0);
        char node2_chr = node2->notation == "~" ? char(node2->left->notation[0] + 32) : node2->notation.at(0);
        return node1_chr < node2_chr;
    });
    return non_janus;
}

Reso I_CNF::resolution(shared_ptr<Node> node, char v)
{
    Reso reso;
    string _v = string(1, char(toupper(v)));
    string _not_v = '~' + _v;

    bool resolutionApplied = false;
    for(auto i = node->variables.begin(), end = node->variables.end();
        i != end; ++i)
    {
        for (auto j = next(i); j != end; ++j)
        {
            if((*i)->variables.size() > 1 || (*j)->variables.size() > 1)
            {
                if(isContain(*i, _v) && isContain(*j, _not_v))
                {
                    reso.resolution->variables.push_back(mergeNode((*i), (*j), _v, _not_v));
                    reso.subtituteSolution->variables.push_back(make_shared<MultiOr>(make_shared<Negate>(make_shared<Variable>(_v))));
                    if(resolutionApplied)
                        reso.subtituteSolution->variables.push_back(make_shared<MultiOr>(make_shared<Variable>(_v)));
                    resolutionApplied = true;
                    (*i)->isRulesReturned = true;
                    (*j)->isRulesReturned = true;
                }
                else if(isContain(*i, _not_v) && isContain(*j, _v))
                {
                    reso.resolution->variables.push_back(mergeNode((*i), (*j), _v, _not_v));
                    reso.subtituteSolution->variables.push_back(make_shared<MultiOr>(make_shared<Variable>(_v)));
                    if(resolutionApplied)
                        reso.subtituteSolution->variables.push_back(make_shared<MultiOr>(make_shared<Negate>(make_shared<Variable>(_v))));

                    resolutionApplied = true;
                    (*i)->isRulesReturned = true;
                    (*j)->isRulesReturned = true;
                }
            }
        }
        if(!(*i)->isRulesReturned)
        {
            reso.resolution->variables.push_back((*i));
            (*i)->isRulesReturned = false;
        }
    }
    getUniqueList(reso.resolution->variables);
    getUniqueList(reso.subtituteSolution->variables);
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
    for(auto e : listNode)
    {
        e->variables.sort([](const shared_ptr<Node> &node1, const shared_ptr<Node> &node2)
                          {
                              char node1_chr = node1->notation[0] == '~' ? char(tolower(node1->left->notation[0])) : node1->notation[0];
                              char node2_chr = node2->notation[0] == '~' ? char(tolower(node2->left->notation[0])) : node2->notation[0];
                              return node1_chr < node2_chr;
                          });

        e->variables.erase(unique(e->variables.begin(), e->variables.end(),
                           [](shared_ptr<Node> &lhs, shared_ptr<Node> &rhs)
                           {
                               return lhs->toString() == rhs->toString();
                           }), e->variables.end());
    }
    getUniqueList(listNode);
    return make_shared<MultiAnd>(listNode);
}

shared_ptr<Node> I_CNF::generateCNF(shared_ptr<Node> originTree)
{
    shared_ptr<Node> tree = originTree->cnfFilter();
    tree = tree->cnfDistribution();
    return tree;
}

bool I_CNF::findJanus(shared_ptr<Node> node)
{
    string singleNode = "";
    for(auto e : node->variables)
    {
        if(e->variables.size() == 1)
            singleNode += e->toString();
    }

    for(auto c : singleNode)
        if('a' <= c && c <= 'z')
        {
            if(singleNode.find(char(toupper(c))) != string::npos)
                return true;
        }
        else
        {
            if(singleNode.find(char(tolower(c))) != string::npos)
                return true;
        }
    return false;
}

void I_CNF::getUniqueList(list<shared_ptr<Node> > &l)
{
    l.sort([](const shared_ptr<Node> &node1, const shared_ptr<Node> &node2)
           {
               string node1_str = node1->toString();
               string node2_str = node2->toString();
               if(node1_str.size() == node2_str.size())
                   return node1_str.compare(node2_str) > 0 ? false : true;
               else
                   return (node1_str.size() < node2_str.size());
           });

    l.erase(unique(l.begin(), l.end(),
                   [](shared_ptr<Node> &lhs, shared_ptr<Node> &rhs)
                   {
                       return lhs->toString() == rhs->toString();
                   }), l.end());
}

bool I_CNF::isContain(shared_ptr<Node> nodes, string v)
{
    for(auto e : nodes->variables)
        if( e->toString() == v )
            return true;
    return false;
}

shared_ptr<Node> I_CNF::mergeNode(shared_ptr<Node> node1, shared_ptr<Node> node2, string v, string not_v)
{
    string tmpStr = "";
    shared_ptr<Node> retNode = make_shared<MultiOr>();

    for(auto e : node1->variables)
        if(e->toString() != v && e->toString() != not_v)
            retNode->variables.push_back(e);

    for(auto e : node2->variables)
        if(!isContain(retNode, e->toString()) && e->toString() != v && e->toString() != not_v)
            retNode->variables.push_back(e);

    retNode->variables.sort([](const shared_ptr<Node> &node1, const shared_ptr<Node> &node2)
    {
        char node1_chr = node1->notation == "~" ? char(node1->left->notation[0] + 32) : node1->notation.at(0);
        char node2_chr = node2->notation == "~" ? char(node2->left->notation[0] + 32) : node2->notation.at(0);
        return node1_chr < node2_chr;
    });

    return retNode;
}
