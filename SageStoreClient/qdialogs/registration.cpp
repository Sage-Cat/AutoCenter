#include "registration.h"
#include "ui_registration.h"

#include <QMessageBox>

Registration::Registration(QWidget *parent, TcpClient *client) :
    QDialog(parent),
    ui(new Ui::Registration),
    client(client)
{
    ui->setupUi(this);
}

Registration::~Registration()
{
    delete ui;
}

void Registration::on_btn_reg_clicked()
{
    // client:::[UID]:::add:::Users:::[name]:::[number]:::[email]:::[ipn]:::[password]
    QStringList requestList = {
        "add",
        "Users",
        ui->line_name->text(),
        ui->line_number->text(),
        ui->line_email->text(),
        ui->line_ipn->text(),
        ui->line_password->text(),
        "0" // LAME: for isAdmin
    };

    QString response = client->send_and_get_response(requestList.join(DELIMITER_MAIN));

    if(response == "1")
        accept();
    else if(response == "0")
        QMessageBox::information(this, "Помилка", "Такий користувач вже існує", QMessageBox::Ok);
    else
        QMessageBox::critical(this, "Помилка", "Такий користувач вже існує", QMessageBox::Ok);
}
