#include "authorization.h"
#include "ui_authorization.h"

#include <QMessageBox>

#include "registration.h"

Authorization::Authorization(QWidget *parent, TcpClient *client) :
    QDialog(parent),
    ui(new Ui::Authorization),
    client(client)
{
    ui->setupUi(this);
}

Authorization::~Authorization()
{
    delete ui;
}

void Authorization::on_btn_login_clicked()
{
    // client:::[UID]:::login:::[login]:::[password]
    QStringList requestList = {
        "login",
        ui->line_number->text(),
        ui->line_password->text()
    };

    if(requestList.at(1) != "" && requestList.at(2) != "")
    {
        QStringList response = client->send_and_get_response(requestList.join(DELIMITER_MAIN)).split(DELIMITER_MAIN);
        if(response.at(0) == "-1")
            QMessageBox::information(this, "", "Невірний логін чи пароль", QMessageBox::Ok);
        else
        {
            client->setUID(response.at(0));
            client->setAdmin(response.at(1).toInt());
            accept();
        }
    }
    else
        QMessageBox::information(this, "Застереження", "Не залишайте поля вводу пустими", QMessageBox::Ok);
}

void Authorization::on_btn_reg_clicked()
{
    Registration *dlg = new Registration(this, client);
    dlg->exec();
    delete dlg;
}
