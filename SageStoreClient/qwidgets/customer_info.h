#ifndef CUSTOMER_INFO_H
#define CUSTOMER_INFO_H

#include <QWidget>

#include <tcpclient.h>

namespace Ui {
class Customer_info;
}

class Customer_info : public QWidget
{
    Q_OBJECT

public:
    explicit Customer_info(QWidget *parent = nullptr, TcpClient *client = new TcpClient());
    ~Customer_info();

private slots:
    void on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime);

    void on_dateTimeEdit_2_dateTimeChanged(const QDateTime &dateTime);

private:
    Ui::Customer_info *ui;
    TcpClient *client;
};

#endif // CUSTOMER_INFO_H
