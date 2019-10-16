#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QThread>
#include <string>
#include "../src/logging.h"
#include "../src/proposition/predicate.h"
#include "../src/cnf/cnf.h"
#include "../src/table/rows.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addStatus(std::string message);
private slots:
    void on_btnParse_clicked();
    void on_btn_showProof_clicked();
    void on_btn_exportGraph_clicked();

private:
    Ui::MainWindow *ui;
    Tree *tree = nullptr;
    string input;
    string QStringtoString(QString str);
    void showTable(QPlainTextEdit &te, list<Rows> table_rows);
    void reset();
};

class appHandler : public handler
{
public:
    appHandler(std::string fn, MainWindow *w);
    void write(std::string msg) override;

private:
    MainWindow *_w;
};
#endif // MAINWINDOW_H
