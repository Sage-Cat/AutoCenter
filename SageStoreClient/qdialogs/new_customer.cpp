#include "new_customer.h"
#include "ui_new_customer.h"

#include <QMessageBox>

New_customer::New_customer(QWidget *parent, TcpClient *client) :
    QDialog(parent),
    ui(new Ui::New_customer),
    client(client)
{
    ui->setupUi(this);
}

New_customer::~New_customer()
{
    delete ui;
}

void New_customer::on_btn_add_clicked()
{
    // client:::[UID]:::add:::Customers:::[name]:::[iban]:::[bank]:::[edrpoy]:::[ipn]:::[address]:::[number]:::[email]
    QStringList requestList = {
        "add",
        "Customers",
        ui->line_name_3->text(),
        ui->line_iban->text(),
        ui->line_bank->text(),
        ui->line_edrpoy->text(),
        ui->line_ipn_3->text(),
        ui->line_address->text(),
        ui->line_number_3->text(),
        ui->line_email_3->text()
    };

    QString result = client->send_and_get_response(requestList.join(DELIMITER_MAIN));

    if(result == "1")
        accept();
    else if(result == "0")
        QMessageBox::information(this, "Помилка", "Не вдалося додати покупця. Клієнт зі схожими ідентифікаторами вже існує", QMessageBox::Ok);
    else
        QMessageBox::information(this, "Помилка", "Помилка сервера", QMessageBox::Ok);
}
