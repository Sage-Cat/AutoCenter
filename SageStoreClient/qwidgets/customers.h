#ifndef CUSTOMERS_H
#define CUSTOMERS_H

#include <QWidget>
#include <QTableWidgetItem>

#include <tcpclient.h>

namespace Ui {
class Customers;
}

class Customers : public QWidget
{
    Q_OBJECT

public:
    explicit Customers(QWidget *parent = nullptr, TcpClient *client = new TcpClient());
    ~Customers();

private slots:
    void on_btn_add_clicked();
    void on_btn_del_clicked();
    void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);

    void on_btn_info_clicked();

    void on_btn_refresh_clicked();

private:
    Ui::Customers *ui;
    TcpClient *client;
    RecordsList recordsList;
};

#endif // CUSTOMERS_H
