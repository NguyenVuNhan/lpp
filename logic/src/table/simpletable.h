#ifndef SIMPLETABLE_H
#define SIMPLETABLE_H

#include "truthtable.h"

class SimpleTable : public TruthTable
{
private:
    list<list<Rows>> getAllRowsGroup();
    list<Rows> getQuineMcCluskey(list<list<Rows>> rowsGroup);
    void simplify();

public:
    explicit SimpleTable(Tree tree);
    explicit SimpleTable(string prop="");
    explicit SimpleTable(Node *tree);
    explicit SimpleTable(TruthTable truthTable);

};

#endif // SIMPLETABLE_H
