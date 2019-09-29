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
    explicit SimpleTable(Tree root);
    explicit SimpleTable(string prop="");
    explicit SimpleTable(shared_ptr<Node> root);
    explicit SimpleTable(TruthTable truthTable);

};

#endif // SIMPLETABLE_H
