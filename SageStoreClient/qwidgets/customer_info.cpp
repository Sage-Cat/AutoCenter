#include "customer_info.h"
#include "ui_customer_info.h"

Customer_info::Customer_info(QWidget *parent, TcpClient *client) :
    QWidget(parent),
    ui(new Ui::Customer_info),
    client(client)
{
    ui->setupUi(this);
}

Customer_info::~Customer_info()
{
    delete ui;
}

void Customer_info::on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{

}

void Customer_info::on_dateTimeEdit_2_dateTimeChanged(const QDateTime &dateTime)
{

}
