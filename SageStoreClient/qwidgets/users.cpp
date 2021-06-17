#include "users.h"
#include "ui_users.h"

Users::Users(QWidget *parent, TcpClient *client) :
    QWidget(parent),
    ui(new Ui::Users),
    client(client)
{
    ui->setupUi(this);
}

Users::~Users()
{
    delete ui;
}

void Users::on_btn_del_clicked()
{

}

void Users::on_btn_save_clicked()
{

}

void Users::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{

}

void Users::on_btn_make_admin_clicked()
{

}
