#include "load_supplier_invoice.h"
#include "ui_load_supplier_invoice.h"

Load_supplier_invoice::Load_supplier_invoice(QWidget *parent, TcpClient *client) :
    QDialog(parent),
    ui(new Ui::Load_supplier_invoice),
    client(client)
{
    ui->setupUi(this);
}

Load_supplier_invoice::~Load_supplier_invoice()
{
    delete ui;
}

void Load_supplier_invoice::on_btn_explorer_clicked()
{

}

void Load_supplier_invoice::on_btn_load_clicked()
{

}
