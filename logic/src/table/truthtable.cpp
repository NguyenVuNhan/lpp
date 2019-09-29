#include <iomanip>
#include "truthtable.h"
#include "../notation/multior.h"

void TruthTable::generateTable()
{
    ulong size = getListVariable().size();
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
        Rows newRow = Rows(var, value, size);

        if(value)
            trueRows.push_back(newRow);
        else
            falseRows.push_back(newRow);
        table.push_back(newRow);

        hash += uintmax_t(value) << var;
    }
}

TruthTable::TruthTable(Tree otherTree)
    : Tree(otherTree.getTree())
{
    generateTable();
}

TruthTable::TruthTable(string prop)
    : Tree(prop)
{
    generateTable();
}

TruthTable::TruthTable(shared_ptr<Node> otherTree)
    : Tree(otherTree)
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
    stringstream ss;
    ss << hex << uppercase << hash;
    return ss.str();
}

Tree TruthTable::getNormalize()
{
    list<shared_ptr<Node> > tmpList;

    for(Rows &i : table)
    {
        if(i.getValue())
        {
            tmpList.push_back(i.toNode(varList));
        }
    }

    return Tree(make_shared<MultiOrNorm>(tmpList));
}
