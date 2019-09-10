#include "truthtable.h"
#include "../notation/or.h"

void TruthTable::generateTable()
{
    ulong size = varList.size();
    for (uintmax_t var = 0; var < (uintmax_t(1)<<size); ++var)
    {
        auto it = varList.begin();
        ulong i = size-1;
        string valList = "";
        while (it != varList.end())
        {
            valList += (*it);
            valList += to_string(var >> i & 0b1);
            it++;
            i--;
        }

        bool value = getValue(valList);
        Rows newRow(var, value);

        table.push_back(newRow);
        if(value)
            trueRows.push_back(newRow);
        else
            falseRows.push_back(newRow);

        hash += uintmax_t(value) << var;
    }
}

TruthTable::TruthTable(Tree tree)
    : Tree(tree.getTree())
{
    generateTable();
}

TruthTable::TruthTable(string prop)
    : Tree(prop)
{
    generateTable();
}

TruthTable::TruthTable(Node *tree)
    : Tree(tree)
{
    generateTable();
}

TruthTable::~TruthTable()
{

}

list<Rows> TruthTable::getTable()
{
    return table;
}

string TruthTable::getHashCode()
{
    return string(hash, 16);
}

Tree TruthTable::getNormalize()
{
    list<Rows>::iterator it = trueRows.begin();
    Node *left = nullptr,
         *right = nullptr;
    do
    {
        Node *newNode = nullptr;

        if(left == nullptr)
            left = newNode;
        else
            right = newNode;

        if(left != nullptr && right != nullptr)
        {
            left = new Or(left, right);
            right = nullptr;
        }
    }
    while(++it != trueRows.end());

    return Tree(left);
}
