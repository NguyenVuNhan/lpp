#ifndef TRUTHTABLE_H
#define TRUTHTABLE_H

#include "../proposition/tree.h"
#include "rows.h"

class TruthTable : public Tree
{
private:
    list<Rows> trueRows;
    list<Rows> falseRows;

    void generateTable();

protected:
    list<Rows> table;
    uintmax_t hash = 0;

public:
    explicit TruthTable(Tree otherTree);
    explicit TruthTable(string prop="");
    explicit TruthTable(shared_ptr<Node> otherTree);
    ~TruthTable();

    list<Rows> getTable();
    string getHashCode();
    Tree getNormalize();
};

#endif // TRUTHTABLE_H
