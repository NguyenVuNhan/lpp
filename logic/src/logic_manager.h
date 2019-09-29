#include "proposition/predicate.h"
#include "proposition/tableaux/semantictableaux.h"
#include "proposition/tableaux/stnode.h"
#include "proposition/tree.h"
#include "table/rows.h"
#include "table/simpletable.h"
#include "table/truthtable.h"

#include "cnf/cnf.h"

class LogicManager
{
public:
    string proposition = "";
    list<string>variables;
    list<string> truthTable;
    list<string> simplifiedTable;
    string dnf = "";
    string nandify = "";
    string cnf = "";

    explicit LogicManager(string prop);

//    string getProposition() { return proposition; }
//    list<string> getVariables() { return variables; }
//    list<string> getTruthTable() { return truthTable; }
//    list<string> getSimplifiedTable() { return simplifiedTable; }
//    string getDNF() { return dnf; }
//    string getNandify() { return nandify; }
//    string getCNF() { return cnf; }
};
