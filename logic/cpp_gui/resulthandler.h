#ifndef RESULTHANDLER_H
#define RESULTHANDLER_H

#include <QString>
#include <QStringList>

struct resultHandler
{
    bool tautology = false;
    QString nand = "NaN";
    QString cnf = "NaN";
    QString satisfiable = "NaN";
    QString dnf_normal = "NaN";
    QString dnf_simple = "NaN";
    QStringList hex;
    QStringList truthTable;
    QStringList simpleTable;
};

#endif // RESULTHANDLER_H
