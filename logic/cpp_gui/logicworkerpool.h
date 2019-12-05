#ifndef TABLEGENERATIONTASK_H
#define TABLEGENERATIONTASK_H

#include <QRunnable>
#include "resulthandler.h"

class TableGenerationTask : public QRunnable
{
    void run() override;
//public:
//    TableGenerationTask();
};

#endif // TABLEGENERATIONTASK_H
