#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "statements.h"
#include "tcpclient.h"

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
    void openTabRecords(int ID_List);

    void on_act_allSales_triggered();
    void on_act_allReceipts_triggered();

private:
    Ui::MainWindow *ui;
    TcpClient *tcpClient;
};
#endif // MAINWINDOW_H
