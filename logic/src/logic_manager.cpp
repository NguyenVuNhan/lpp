#include "logic_manager.h"
#include "utils.h"

logic::logic(string prop)
{
    if(isContain(prop, list<char>({'@', '!'})))
    {
        Predicate tree(prop);
        proposition = tree.getProposition();
        variables = tree.getListVariable();
    }
    else if(isContain(prop, list<char>({'[', ']'})))
    {
        CNF cnf(prop);
        proposition = cnf.getProposition();
        cnf = proposition;
    }
    else
    {
        Tree tree(prop);
        proposition = tree.getProposition();
        variables = tree.getListVariable();
        TruthTable table(tree);
        string row;
        for(Rows tableRow : table.getTable())
        {
            row = "";
            for(char c : tableRow.getElem())
                row += c + ' ';
            truthTable.push_back(row);
        }
    }
}
