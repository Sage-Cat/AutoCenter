#include "new_seller.h"
#include "ui_new_seller.h"

#include <QMessageBox>

New_seller::New_seller(QWidget *parent, TcpClient *client) :
    QDialog(parent),
    ui(new Ui::New_seller),
    client(client)
{
    ui->setupUi(this);
}

New_seller::~New_seller()
{
    delete ui;
}

void New_seller::on_btn_add_clicked()
{
    // client:::[UID]:::add:::Sellers:::[name]:::[iban]:::[bank]:::[edrpoy]:::[ipn]:::[address]
    QStringList requestList = {
        "add",
        "Sellers",
        ui->line_name_3->text(),
        ui->line_iban->text(),
        ui->line_bank->text(),
        ui->line_edrpoy->text(),
        ui->line_ipn_3->text(),
        ui->line_address->text()
    };

    QString result = client->send_and_get_response(requestList.join(DELIMITER_MAIN));

    if(result == "1")
        accept();
    else if(result == "0")
        QMessageBox::information(this, "Помилка", "Не вдалося додати продавця. Продавець зі схожими ідентифікаторами вже існує", QMessageBox::Ok);
    else
        QMessageBox::information(this, "Помилка", "Помилка сервера", QMessageBox::Ok);
}
