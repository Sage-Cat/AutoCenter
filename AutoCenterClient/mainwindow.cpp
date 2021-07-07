#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QIcon>

#include "widgets/lists.h"
#include "widgets/records.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Network */
    tcpClient = new TcpClient();
    thread = new QThread;
    networkCommunication = new NetworkCommunication(tcpClient);

    tcpClient->moveToThread(thread);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    thread->start();   

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

void MainWindow::openTabLists(OperationType type)
{
    Lists *tab = new Lists(this, networkCommunication, type);
    QString label = "";

    if(type == OperationType::sale)
        label = "Усі продажі";
    else
        label = "Усі надходження";

    ui->tabWidget->addTab(tab, QIcon(":/icons/page.png"), label);

    connect(tab, &Lists::tabRecordsRequested, this, &MainWindow::openTabRecords);
}

void MainWindow::openTabRecords(int ID_List)
{
    Records *tab = new Records(this, networkCommunication, ID_List);
    ui->tabWidget->addTab(tab, QIcon(":/icons/sale.png"), "Редагування списку");
    ui->tabWidget->setCurrentWidget(tab);
}

void MainWindow::on_act_allSales_triggered()
{
    openTabLists(OperationType::sale);
}

void MainWindow::on_act_allReceipts_triggered()
{
    openTabLists(OperationType::receipt);
}
