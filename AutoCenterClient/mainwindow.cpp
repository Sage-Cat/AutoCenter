#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QIcon>

#include "widgets/lists.h"
#include "widgets/records.h"
#include "widgets/info.h"
#include "widgets/persons.h"

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
    ui->tabWidget->setCurrentWidget(tab);

    connect(tab, &Lists::tabRecordsRequested, this, &MainWindow::openTabRecords);
}

void MainWindow::openTabRecords(int ID_List, OperationType type)
{
    Records *tab = new Records(this, networkCommunication, ID_List, type);
    ui->tabWidget->addTab(tab, QIcon(":/icons/sale.png"), "Редагування списку");
    ui->tabWidget->setCurrentWidget(tab);
}

void MainWindow::openTabPersons(Tables table, QIcon icon, QString label)
{
    Persons *tab = new Persons(this, networkCommunication, table);
    ui->tabWidget->addTab(tab, icon, label);
    ui->tabWidget->setCurrentWidget(tab);

    connect(tab, &Persons::tabInfoRequested, this, &MainWindow::openTabInfo);
}

void MainWindow::openTabInfo(Tables table, int ID)
{
    Info *tab = new Info(this, networkCommunication, table, ID);
    ui->tabWidget->addTab(tab, QIcon(":/icons/info.png"), "Інформація");
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

void MainWindow::on_act_customers_triggered()
{
    openTabPersons(Tables::customers, QIcon(":/icons/customer.png"), "Покупці");
}


void MainWindow::on_act_sellers_triggered()
{
    openTabPersons(Tables::sellers, QIcon(":/icons/seller.png"), "Продавці");
}


void MainWindow::on_act_users_triggered()
{
    openTabPersons(Tables::users, QIcon(":/icons/crown.png"), "Користувачі");
}

