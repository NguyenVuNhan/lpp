#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../src/table/simpletable.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    SET_LOGGING_HANDLER(new appHandler("logic.log", this))
    INFO("Initiallize")

    ui->tb_prefix->setReadOnly(true);
    ui->tb_variables->setReadOnly(true);
    ui->btn_showProof->setVisible(false);
    ui->te_truthtable->setReadOnly(true);
    ui->te_hex->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete tree;
    delete ui;
}

void MainWindow::addStatus(string message)
{
    ui->te_log->appendPlainText(QString::fromStdString(message));
}

void MainWindow::on_btnParse_clicked()
{
    this->setEnabled(false);
    ui->btnParse->setEnabled(false);
    string tmpInput = ui->tb_input->toPlainText().toStdString();
    if(input == tmpInput)
    {
        ui->btnParse->setEnabled(true);
        return;
    }
    reset();

    input = tmpInput;
    INFO(input)

    if (input.find('!') != string::npos || input.find('@') != string::npos)
    {
        tree = new Predicate(input);
        ui->tb_prefix->setText(QString::fromStdString(tree->getProposition()));
        if(tree->isTautology())
        {
            ui->btn_showProof->setVisible(true);
        }
        string tmpStr = "";
        for(string str : tree->getListVariable())
        {
            tmpStr += str + ' ';
        }
        ui->tb_variables->setText(QString::fromStdString(tmpStr));
    }
    else
    {
        if (input.find('[') != string::npos || input.find(']') != string::npos)
        {
            tree = new CNF(input);
        }
        else
        {
            tree = new Tree(input);
            // -------------------------------------------------------------------
            Tree nand(tree->getTree()->nandify());
            ui->tb_nand->setText(QString::fromStdString(nand.getProposition()));
            TruthTable nand_table(nand);
            ui->te_hex->appendPlainText("Nand norm hash\t\t: " + QString::fromStdString(nand_table.getHashCode()));
            SimpleTable nand_simple_table(nand_table);
            ui->te_hex->appendPlainText("Nand simple hash\t\t: " + QString::fromStdString(nand_simple_table.getHashCode()));
            ui->te_hex->appendPlainText("------------------------------------------------");
        }
        // -------------------------------------------------------------------
        string tmpStr = "";
        for(string str : tree->getListVariable())
        {
            tmpStr += str + ' ';
        }
        ui->tb_variables->setText(QString::fromStdString(tmpStr));
        // -------------------------------------------------------------------
        CNF cnf(tree->getTree());
        ui->tb_cnf->setText(QString::fromStdString(cnf.getProposition()));
        TruthTable cnf_table(cnf.getTree());
        ui->te_hex->appendPlainText("CNF table hash\t\t: " + QString::fromStdString(cnf_table.getHashCode()));
        TruthTable cnf_simplified_table(cnf_table);
        ui->te_hex->appendPlainText("CNF simple table hash\t: " + QString::fromStdString(cnf_simplified_table.getHashCode()));
        ui->tb_satisfiable->setText(QString::fromStdString(cnf.getDavidPutnam()));
        ui->tb_prefix->setText(QString::fromStdString(tree->getProposition()));
        // -------------------------------------------------------------------
        if(tree->isTautology())
        {
            ui->btn_showProof->setVisible(true);
        }
        // -------------------------------------------------------------------
        TruthTable table(tree->getTree());
        showTable(*ui->te_truthtable, table.getTable());
        ui->te_hex->appendPlainText("Truth table hash\t\t: " + QString::fromStdString(table.getHashCode()));
        SimpleTable s_table(table);
        showTable(*ui->te_simpletable, s_table.getTable());
        ui->te_hex->appendPlainText("Simplified table hash\t\t: " + QString::fromStdString(s_table.getHashCode()));
        ui->te_hex->appendPlainText("------------------------------------------------");
        // -------------------------------------------------------------------
        Tree dnf_normal = table.getNormalize();
        ui->tb_dnf_normal->setText(QString::fromStdString(dnf_normal.getProposition()));
        TruthTable dnf_normal_table(dnf_normal);
        ui->te_hex->appendPlainText("DNF norm hash\t\t: " + QString::fromStdString(dnf_normal_table.getHashCode()));
        Tree dnf_simple = s_table.getNormalize();
        ui->tb_dnf_simple->setText(QString::fromStdString(dnf_simple.getProposition()));
        TruthTable dnf_simple_table(dnf_simple);
        ui->te_hex->appendPlainText("DNF simplified hash\t\t: " + QString::fromStdString(dnf_simple_table.getHashCode()));
    }

    ui->btnParse->setEnabled(true);
    this->setEnabled(true);
}

string MainWindow::QStringtoString(QString str)
{
    return str.toUtf8().constData();
}

void MainWindow::showTable(QPlainTextEdit &te, list<Rows> table_rows)
{
    te.appendPlainText(ui->tb_variables->toPlainText() + 'v');
    for(Rows r : table_rows)
    {
        te.appendPlainText(QString::fromStdString(r.toString()));
    }
}

void MainWindow::reset()
{
    delete tree;
    tree = nullptr;
    ui->te_truthtable->clear();
    ui->te_simpletable->clear();
    ui->te_hex->clear();

    ui->tb_cnf->clear();
    ui->tb_nand->clear();
    ui->tb_prefix->clear();
    ui->tb_variables->clear();
    ui->tb_dnf_normal->clear();
    ui->tb_dnf_simple->clear();
    ui->tb_satisfiable->clear();

    ui->btn_showProof->setVisible(false);
}

void MainWindow::on_btn_showProof_clicked()
{
    tree->exportProof("LPP_Proof", "../LPP_Proof.dot");
    system("dot -Tpng -O ../LPP_Proof.dot");
    system("eog ../LPP_Proof.dot.png");
}

void MainWindow::on_btn_exportGraph_clicked()
{
    tree->exportGraph("LPP", "../LPP.dot");
    system("dot -Tpng -O ../LPP.dot");
    system("eog ../LPP.dot.png");
}

appHandler::appHandler(string fn, MainWindow *w)
    : handler(fn)
    , _w(w)
{

}

void appHandler::write(string msg)
{
    _w->addStatus(msg);
    ofs << msg;
}

