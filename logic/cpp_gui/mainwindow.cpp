#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCursor>
#include <QMetaType>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    appHandler *h = new appHandler("logic.log", this);
    qRegisterMetaType<std::string>();
    connect(h, &appHandler::addStatus, this, &MainWindow::onAddStatus);
    SET_LOGGING_HANDLER(h)
    ui->setupUi(this);
    qRegisterMetaType<QTextCursor>("QTextCursor");

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

void MainWindow::get_CNF_thread(Tree* tree, resultHandler &rh)
{
    INFO("Generating CNF")
    CNF cnf(tree->getTree());
    rh.cnf = QString::fromStdString(cnf.getProposition());
    TruthTable cnf_table(cnf.getTree());
    rh.hex.append("CNF table hash\t\t: " + QString::fromStdString(cnf_table.getHashCode()));
    SimpleTable cnf_simplified_table(cnf_table);
    rh.hex.append("CNF simple table hash\t\t: " + QString::fromStdString(cnf_simplified_table.getHashCode()));
    rh.satisfiable = QString::fromStdString(cnf.getDavidPutnam());
}

void MainWindow::get_tautology_thread(Tree *tree, resultHandler &rh)
{
    INFO("Getting tautology")
    if(tree->isTautology())
    {
        rh.tautology = true;
    }
}

void MainWindow::get_table_thread(Tree *tree, resultHandler &rh)
{
    INFO("Generating table")
    TruthTable table(tree->getTree());
    rh.truthTable.append(ui->tb_variables->toPlainText() + 'v');
    for(Rows r : table.getTable())
    {
        rh.truthTable.append(QString::fromStdString(r.toString()));
    }
    rh.hex.append("Truth table hash\t\t: " + QString::fromStdString(table.getHashCode()));

    INFO("Generating simple table")
    SimpleTable s_table(table);
    rh.simpleTable.append(ui->tb_variables->toPlainText() + 'v');
    for(Rows r : s_table.getTable())
    {
        rh.simpleTable.append(QString::fromStdString(r.toString()));
    }
    rh.hex.append("Simplified table hash\t\t: " + QString::fromStdString(s_table.getHashCode()));

    std::thread t_normalize(&MainWindow::get_normalize_thread, this, table, std::ref(rh));
    t_normalize.join();

    std::thread t_s_normalize(&MainWindow::get_normalize_thread, this, s_table, std::ref(rh));
    t_s_normalize.join();
}

void MainWindow::get_normalize_thread(TruthTable table, resultHandler &rh)
{
    INFO("Generating dnf")
    Tree dnf_normal = table.getNormalize();
    rh.dnf_normal = QString::fromStdString(dnf_normal.getProposition());
    TruthTable dnf_normal_table(dnf_normal);
    rh.hex.append("DNF norm hash\t\t: " + QString::fromStdString(dnf_normal_table.getHashCode()));
}

void MainWindow::get_s_normalize_thread(SimpleTable table, resultHandler &rh)
{
    Tree dnf_simple = table.getNormalize();
    rh.dnf_simple = QString::fromStdString(dnf_simple.getProposition());
    TruthTable dnf_simple_table(dnf_simple);
    rh.hex.append("DNF simplified hash\t\t: " + QString::fromStdString(dnf_simple_table.getHashCode()));
}

void MainWindow::on_btnParse_clicked()
{
    this->setEnabled(false);
    ui->btnParse->setEnabled(false);
    string tmpInput = ui->tb_input->toPlainText().toStdString();
    if(input == tmpInput)
    {
        ui->btnParse->setEnabled(true);
        this->setEnabled(true);
        return;
    }
    reset();

    input = tmpInput;
    INFO(input)

    if (input.find('!') != string::npos || input.find('@') != string::npos)
    {
        tree = new Predicate(input);
        ui->tb_prefix->setText(QString::fromStdString(tree->getProposition()));
        std::thread t_tautology(&MainWindow::get_tautology_thread, this, tree, std::ref(rh));
        string tmpStr = "";
        for(string str : tree->getListVariable())
        {
            tmpStr += str + ' ';
        }
        ui->tb_variables->setText(QString::fromStdString(tmpStr));
        t_tautology.join();
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
        ui->tb_prefix->setText(QString::fromStdString(tree->getProposition()));
        string tmpStr = "";
        for(string str : tree->getListVariable())
        {
            tmpStr += str + ' ';
        }
        ui->tb_variables->setText(QString::fromStdString(tmpStr));
        // -------------------------------------------------------------------
        std::thread t_cnf(&MainWindow::get_CNF_thread, this, tree, std::ref(rh));
        // -------------------------------------------------------------------
        std::thread t_tautology(&MainWindow::get_tautology_thread, this, tree, std::ref(rh));
        // -------------------------------------------------------------------
        std::thread t_table(&MainWindow::get_table_thread, this, tree, std::ref(rh));

        t_cnf.join();
        t_tautology.join();
        t_table.join();
    }

    ui->tb_cnf->setText(rh.cnf);
    ui->tb_satisfiable->setText(rh.satisfiable);
    ui->tb_dnf_normal->setText(rh.dnf_normal);
    ui->tb_dnf_simple->setText(rh.dnf_simple);
    for (QString e : rh.hex) {
        ui->te_hex->appendPlainText(e);
    }
    for (QString e : rh.truthTable) {
        ui->te_truthtable->appendPlainText(e);
    }
    for (QString e : rh.simpleTable) {
        ui->te_simpletable->appendPlainText(e);
    }

    ui->btn_showProof->setVisible(rh.tautology);
    ui->btnParse->setEnabled(true);
    this->setEnabled(true);
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

    rh = resultHandler();
}

void MainWindow::onAddStatus(string message)
{
    ui->te_log->appendPlainText(QString::fromStdString(message));
}

void MainWindow::ui_set_tb_cnf(QString msg)
{
    rh.cnf = msg;
    qDebug() << msg;
}

void MainWindow::ui_set_te_hex(QString msg)
{
    rh.hex.append(msg);
    qDebug() << msg;
}

void MainWindow::ui_set_tb_satisfiable(QString msg)
{
    rh.satisfiable = msg;
    qDebug() << msg;
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

appHandler::appHandler(string fn, QObject *parent)
    : QObject(parent)
    , handler(fn) { }

void appHandler::write(string msg)
{
    emit addStatus(msg);
    ofs << msg;
}
