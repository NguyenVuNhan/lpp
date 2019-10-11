#include "simpletable.h"
#include "../utils.h"

SimpleTable::SimpleTable(Tree root)
    : TruthTable(root)
{
    simplify();
}

SimpleTable::SimpleTable(string prop)
    : TruthTable(prop)
{
    simplify();
}

SimpleTable::SimpleTable(shared_ptr<Node> root)
    : TruthTable(root)
{
    simplify();
}

SimpleTable::SimpleTable(TruthTable truthTable)
    : TruthTable(truthTable.getTree())
{
    simplify();
}

void SimpleTable::simplify()
{
    list<list<Rows>> group = getAllRowsGroup();
    table = getQuineMcCluskey(group);

    // get hash
    int index = 0;
    hash = 0;
    for (auto row : table)
    {
        hash += static_cast<uintmax_t>(row.getValue()) << index++;
    }
}

list<list<Rows> > SimpleTable::getAllRowsGroup()
{
    list<list<Rows> > groupRows;

    ulong nrOfVariable = getListVariable().size();
    for (ulong i = 0; i <= nrOfVariable; i++)
    {
        groupRows.push_back(list<Rows>());
    }

    for (Rows row : table)
    {
        int count = 0;
        for (ulong k = 0; k < nrOfVariable; k++)
        {
            if(row.elem_str[k] == '1')
            {
                count++;
            }
        }

        auto it = next(groupRows.begin(), count);
        (*it).push_back(row);
    }
    return  groupRows;
}

list<Rows> SimpleTable::getQuineMcCluskey(list<list<Rows> > rowsGroup)
{
    // in case rowsGroup already epmty
    if(rowsGroup.size() == 0)
    {
        return  list<Rows>();
    }

    list<list<Rows>> tmpGroupRows;
    bool isSimplified = true;
    for (auto i = rowsGroup.begin(), list_end = prev(rowsGroup.end()); i != list_end; i++)
    {
        list<Rows> tmpRows;
        for (auto j = i->begin(); j != i->end(); j++)
        {
            for (auto k = next(i)->begin(); k != next(i)->end(); k++)
            {
                int pos = j->is_match_pair(*k);
                if  (pos >= 0)
                {
                    isSimplified = false;
                    Rows tmpRow = *j;
                    tmpRow.setDontCare(static_cast<uint>(pos));
                    tmpRows.push_back(tmpRow);
                    j->checked = true;
                    k->checked = true;
                }
            }

            if(!j->checked)
            {
                tmpRows.push_back(*j);
            }
        }
        // remove douplicate
        tmpRows.sort();
        tmpRows.unique();
        tmpGroupRows.push_back(tmpRows);
    }

    // check for last group
    list<Rows> tmpRows;
    for (auto row : (*prev(rowsGroup.end())))
    {
        if(!row.checked)
        {
            tmpRows.push_back(row);
        }
    }
    if(tmpRows.size() > 0)
    {
        // remove douplicate
        tmpRows.sort();
        tmpRows.unique();
        tmpGroupRows.push_back(tmpRows);
    }

    if(isSimplified)
    {
        list<Rows> return_list;
        for (auto group : tmpGroupRows)
        {
            return_list.splice(return_list.end(), group);
        }
        return return_list;
    }
    else
    {
        return getQuineMcCluskey(tmpGroupRows);
    }
}
