#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>

#include "statements.h"
#include "tcpclient.h"
#include "networkcommunication.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void closeTab(int);

    void openTabLists(OperationType type);
    void openTabRecords(int ID_List, OperationType type);
    void openTabPersons(Tables table, QIcon icon, QString label);
    void openTabInfo(Tables table, int ID);

    void on_act_allSales_triggered();
    void on_act_allReceipts_triggered();

private slots:
    void on_act_customers_triggered();
    void on_act_sellers_triggered();
    void on_act_users_triggered();

private:
    Ui::MainWindow *ui;
    TcpClient *tcpClient;
    QThread *thread;
    NetworkCommunication *networkCommunication;
};
#endif // MAINWINDOW_H
