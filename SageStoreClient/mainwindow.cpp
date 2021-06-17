#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

#include "qdialogs/authorization.h"
#include "qwidgets/customers.h"
#include "qwidgets/sellers.h"
#include "qdialogs/load_supplier_pricelist.h"
#include "qwidgets/customer_info.h"
#include "qwidgets/user_logs.h"

#include "qwidgets/users.h"
#include "qwidgets/records.h"
#include "qwidgets/lists.h"
#include "qwidgets/inventory.h"
#include "qwidgets/statistics.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    client(new TcpClient)
{
    ui->setupUi(this);

    // Network connections
    connect(client, SIGNAL(errorDetected(QString)), this, SLOT(handleCriticalError(QString)));

    /* Authorization and Registration */
    this->setHidden(true);

    Authorization *dlg = new Authorization(this, client);
    if(dlg->exec() == QDialog::Rejected)
        this->~MainWindow();

    this->setHidden(false);

    connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_act_users_triggered()
{
    Users * tab = new Users();
    ui->tabWidget->addTab(tab, QIcon(":/icons/users.png"), "Користувачі");
    ui->tabWidget->setCurrentWidget(tab);

}

void MainWindow::on_act_allSales_triggered()
{
    Lists * tab = new Lists();
    ui->tabWidget->addTab(tab, QIcon(":/icons/page.png"), "Списки");
    ui->tabWidget->setCurrentWidget(tab);

    connect(tab, SIGNAL(openRecords()), this, SLOT(toOpenRecords()));
}

void MainWindow::on_act_accounts_triggered()
{
    on_act_allSales_triggered();
}

void MainWindow::on_act_expenceInvoices_triggered()
{
    on_act_allSales_triggered();
}

void MainWindow::on_act_returnInvoices_triggered()
{
    on_act_allSales_triggered();
}

void MainWindow::on_act_taxInvoices_triggered()
{
    on_act_allSales_triggered();
}

void MainWindow::on_act_allReceipts_triggered()
{
    
}

void MainWindow::on_act_loadReceipt_triggered()
{
    on_act_allSales_triggered();
}

void MainWindow::on_act_exit_triggered()
{
    this->~MainWindow();
}

void MainWindow::on_act_inventory_triggered()
{
    Inventory * tab = new Inventory();
    ui->tabWidget->addTab(tab, QIcon(":/icons/work.png"), "Інвентар");
    ui->tabWidget->setCurrentWidget(tab);
}

void MainWindow::on_act_customers_triggered()
{
    Customers *tab = new Customers(this, client);
    ui->tabWidget->addTab(tab, QIcon(":/icons/customer.png"), "Покупці");
    ui->tabWidget->setCurrentWidget(tab);
}

void MainWindow::on_act_sellers_triggered()
{
    Sellers *tab = new Sellers(this, client);
    ui->tabWidget->addTab(tab, QIcon(":/icons/seller.png"), "Продавці");
    ui->tabWidget->setCurrentWidget(tab);
}

void MainWindow::on_act_loadPriceList_triggered()
{
    Load_supplier_pricelist *dlg = new Load_supplier_pricelist(this, client);
    if(dlg->exec() == QDialog::Accepted)
    {

    }
}

void MainWindow::on_act_statistics_triggered()
{
    Statistics *tab = new Statistics(this, client);
    ui->tabWidget->addTab(tab, QIcon(":/icons/sale.png"), "Статистика");
    ui->tabWidget->setCurrentWidget(tab);
}

void MainWindow::toOpenRecords()
{
    Records *tab = new Records(this, client);
    ui->tabWidget->addTab(tab, QIcon(":/icons/goods.ico"), "Список товарів");
    ui->tabWidget->setCurrentWidget(tab);
}

void MainWindow::closeTab(int index)
{
    ui->tabWidget->removeTab(index);
}

void MainWindow::handleCriticalError(QString error_message)
{
    QMessageBox::critical(this, "Помилка", error_message, QMessageBox::Ok);
    QMessageBox::critical(this, "Помилка", "Перезапусти програму. А якщо не допоможе, то проконсультуйся у програміста", QMessageBox::Ok);
    this->~MainWindow();
}
