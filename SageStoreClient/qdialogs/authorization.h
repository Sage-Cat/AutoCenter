#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QDialog>

#include <tcpclient.h>

namespace Ui {
class Authorization;
}

class Authorization : public QDialog
{
    Q_OBJECT

public:
    explicit Authorization(QWidget *parent = nullptr, TcpClient *client = new TcpClient());
    ~Authorization();

private slots:
    void on_btn_login_clicked();
    void on_btn_reg_clicked();
    
private:
    Ui::Authorization *ui;
    TcpClient *client;
};

#endif // AUTHORIZATION_H
