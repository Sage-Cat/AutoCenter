#include "addproduct.h"
#include "ui_addproduct.h"

AddProduct::AddProduct(QWidget *parent, NetworkCommunication *networkCommunication) :
    QDialog(parent),
    ui(new Ui::AddProduct),
    networkCommunication(networkCommunication)
{
    ui->setupUi(this);
}

AddProduct::~AddProduct()
{
    delete ui;
}

void AddProduct::on_btn_add_clicked()
{
    QStringList requestList = {
        SERVER_API[Api::_add],
        DATABASE_TABLES[Tables::products],
        "NULL", // ID is autoincremented
        "'" + ui->line_code->text() + "'",
        "'" + ui->line_catalog->text() + "'",
        "'" + ui->line_tnved->text() + "'",
        "'" + ui->line_name->text() + "'",
        "'" + ui->line_unit->text() + "'",
    };

    // send request
    emit networkCommunication->requestReady(requestList.join(DELIMITERS[Delimiters::primary]));

    // get response
    QString response = networkCommunication->getResponseWhenReady();
    if(response == "-1")
    {
        QMessageBox::critical(nullptr, "Помилка AddProduct", "on_btn_add_clicked", QMessageBox::Ok);
        this->reject();
    }

    ID_Product = response;

    this->accept();
}

const QString &AddProduct::getID_Product() const
{
    return ID_Product;
}

