#include "notation/and.h"
#include "notation/biimplicate.h"
#include "notation/implicate.h"
#include "notation/multiand.h"
#include "notation/multior.h"
#include "notation/negate.h"
#include "notation/node.h"
#include "notation/or.h"
#include "notation/value.h"
#include "notation/variable.h"
#include "notation/nand.h"
#include "notation/statement.h"
#include "notation/forall.h"
#include "notation/exists.h"

#include "proposition/predicate.h"
#include "proposition/tableaux/semantictableaux.h"
#include "proposition/tableaux/stnode.h"
#include "proposition/tree.h"
#include "table/rows.h"
#include "table/simpletable.h"
#include "table/truthtable.h"

#include "cnf/cnf.h"

struct logic {
    logic(string prop);
    string proposition = "";
    list<string>variables;
    list<string> truthTable;
    list<string> simplifiedTable;
    string dnf = "";
    string nandify = "";
    string cnf = "";

    string getProposition() { return proposition; }

    list<string> getVariables() { return variables; }

    list<string> getTruthTable() { return truthTable; }

    list<string> getSimplifiedTable() { return simplifiedTable; }

    string getDNF() { return dnf; }

    string getNandify() { return nandify; }

    string getCNF() { return cnf; }
};
