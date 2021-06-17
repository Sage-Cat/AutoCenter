#include "user_logs.h"
#include "ui_user_logs.h"

User_logs::User_logs(QWidget *parent, TcpClient *client) :
    QWidget(parent),
    ui(new Ui::User_logs),
    client(client)
{
    ui->setupUi(this);
}

User_logs::~User_logs()
{
    delete ui;
}


void User_logs::on_dateTime_from_dateTimeChanged(const QDateTime &dateTime)
{

}

void User_logs::on_dateTime_to_dateTimeChanged(const QDateTime &dateTime)
{

}
