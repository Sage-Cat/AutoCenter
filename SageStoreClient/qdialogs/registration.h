#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QDialog>

#include <tcpclient.h>

namespace Ui {
class Registration;
}

class Registration : public QDialog
{
    Q_OBJECT

public:
    explicit Registration(QWidget *parent = nullptr, TcpClient *client = new TcpClient());
    ~Registration();

private slots:
    void on_btn_reg_clicked();

private:
    Ui::Registration *ui;
    TcpClient *client;
};

#endif // REGISTRATION_H
