#ifndef NEW_SELLER_H
#define NEW_SELLER_H

#include <QDialog>

#include <tcpclient.h>

namespace Ui {
class New_seller;
}

class New_seller : public QDialog
{
    Q_OBJECT

public:
    explicit New_seller(QWidget *parent = nullptr, TcpClient *client = new TcpClient());
    ~New_seller();

private slots:
    void on_btn_add_clicked();

private:
    Ui::New_seller *ui;
    TcpClient *client;
};

#endif // NEW_SELLER_H
