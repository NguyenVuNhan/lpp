#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QThread>
#include <string>
#include <thread>
#include "resulthandler.h"
#include "mythread.h"
#include "../src/logging.h"
#include "../src/proposition/predicate.h"
#include "../src/cnf/cnf.h"
#include "../src/table/rows.h"
#include "../src/table/simpletable.h"

class CNFWorker;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void onAddStatus(std::string message);
    void on_btnParse_clicked();
    void on_btn_showProof_clicked();
    void on_btn_exportGraph_clicked();

    // Thread handler
    void ui_set_tb_cnf(QString);
    void ui_set_te_hex(QString);
    void ui_set_tb_satisfiable(QString);

signals:
    void changeFinished();

private:
    Ui::MainWindow *ui;
    Tree *tree = nullptr;
    string input;
    resultHandler rh;

    void get_CNF_thread(Tree *tree, resultHandler &rh);
    void get_tautology_thread(Tree *tree, resultHandler &rh);
    void get_table_thread(Tree *tree, resultHandler &rh);
    void get_normalize_thread(TruthTable table, resultHandler &rh);
    void get_s_normalize_thread(SimpleTable table, resultHandler &rh);
    void reset();
};

class appHandler : public QObject,
                    public handler
{
    Q_OBJECT
public:
    appHandler(std::string fn, QObject *parent = nullptr);
    void write(std::string msg) override;
signals:
    void addStatus(std::string msg);
};

Q_DECLARE_METATYPE(std::string)

#endif // MAINWINDOW_H
