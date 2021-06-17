#ifndef USERS_H
#define USERS_H

#include <QWidget>
#include <QTableWidgetItem>

#include <tcpclient.h>

namespace Ui {
class Users;
}

class Users : public QWidget
{
    Q_OBJECT

public:
    explicit Users(QWidget *parent = nullptr, TcpClient *client = new TcpClient());
    ~Users();

private slots:
    void on_btn_del_clicked();
    void on_btn_save_clicked();
    void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);

    void on_btn_make_admin_clicked();

private:
    Ui::Users *ui;
    TcpClient *client;
};

#endif // USERS_H
