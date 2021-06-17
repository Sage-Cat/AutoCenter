#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "tcpclient.h"
#include "statements.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_act_users_triggered();
    void on_act_allSales_triggered();
    void on_act_accounts_triggered();
    void on_act_expenceInvoices_triggered();
    void on_act_returnInvoices_triggered();
    void on_act_taxInvoices_triggered();
    void on_act_allReceipts_triggered();
    void on_act_loadReceipt_triggered();
    void on_act_exit_triggered();
    void on_act_inventory_triggered();
    void on_act_customers_triggered(); 
    void on_act_sellers_triggered();
    void on_act_loadPriceList_triggered();
    void on_act_statistics_triggered();

    void toOpenRecords();
    void closeTab(int);

    //! Error handling
    void handleCriticalError(QString error_message);
    
private:
    Ui::MainWindow *ui;
    TcpClient *client;

};
#endif // MAINWINDOW_H
