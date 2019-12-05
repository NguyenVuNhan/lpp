#ifndef MYTHYREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QDebug>

#include "../src/proposition/tree.h"
#include "resulthandler.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct resultHandler;

class STWorker : public QThread
{
    Q_OBJECT
public:
    STWorker(QObject *parent = nullptr) : QThread(parent)  { }
    ~STWorker() override  { qDebug() << "finish"; }

    void requestData(Tree *tree, resultHandler *rh);
    void run() override;

private:
    Tree *_tree;
    resultHandler *_rh;
};

#endif // MYTHYREAD_H
