#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QIcon>

#include "widgets/lists.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Authorization and Registration */
    this->setHidden(true);

    this->setHidden(false);

    connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeTab(int index)
{
    ui->tabWidget->removeTab(index);
}

void MainWindow::openTabLists(Op_type type)
{
    Lists *tab = new Lists(this, type);
    QString label = "";

    if(type == Op_type::sale)
        label = "Усі продажі";
    else
        label = "Усі надходження";

    ui->tabWidget->addTab(tab, QIcon(":/icons/page.png"), label);
}

void MainWindow::openTabRecords(int ID_List)
{

}

void MainWindow::on_act_allSales_triggered()
{
    openTabLists(Op_type::sale);
}

void MainWindow::on_act_allReceipts_triggered()
{
    openTabLists(Op_type::receipt);
}
