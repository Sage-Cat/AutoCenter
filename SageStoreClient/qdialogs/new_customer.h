#ifndef NEW_CUSTOMER_H
#define NEW_CUSTOMER_H

#include <QDialog>

#include <tcpclient.h>

namespace Ui {
class New_customer;
}

class New_customer : public QDialog
{
    Q_OBJECT

public:
    explicit New_customer(QWidget *parent = nullptr, TcpClient *client = new TcpClient());
    ~New_customer();

private slots:
    void on_btn_add_clicked();

private:
    Ui::New_customer *ui;
    TcpClient *client;
};

#endif // NEW_CUSTOMER_H
