#include "mythread.h"
#include "ui_mainwindow.h"
#include "../src/cnf/cnf.h"
#include "../src/table/rows.h"
#include "../src/table/simpletable.h"
#include <iostream>
#include <string>

void STWorker::requestData(Tree *tree, resultHandler *rh)
{
    _tree = tree;
    _rh = rh;
    if(!isRunning())
        start();
}

void STWorker::run()
{
    if(_tree != nullptr)
    {
        CNF cnf(_tree->getTree());
        TruthTable cnf_table(cnf.getTree());
        TruthTable cnf_simplified_table(cnf_table);

        _rh->cnf = QString::fromStdString(cnf.getProposition());
        //TODO: Unknown issue
        cnf.getDavidPutnam();
        _rh->satisfiable = QString::fromStdString(cnf.getDavidPutnam());
        _rh->hex.append("CNF table hash\t: " + QString::fromStdString(cnf_table.getHashCode()));
        _rh->hex.append("CNF simple table hash\t: " + QString::fromStdString(cnf_simplified_table.getHashCode()));
    }
}
