#include "addperson.h"
#include "ui_addperson.h"

AddPerson::AddPerson(QWidget *parent, NetworkCommunication *networkCommunication, Tables table, QString ID) :
    QDialog(parent),
    ui(new Ui::AddPerson),
    networkCommunication(networkCommunication),
    table(table),
    ID(ID)
{
    ui->setupUi(this);

    /* GUI SETUP */
    if(table == Tables::sellers)
    {
        ui->line_number->setHidden(true);
        ui->label_number->setHidden(true);

        ui->line_email->setHidden(true);
        ui->label_email->setHidden(true);

        ui->line_password->setHidden(true);
        ui->label_password->setHidden(true);
    }
    else if(table == Tables::users)
    {
        ui->line_iban->setHidden(true);
        ui->label_iban->setHidden(true);

        ui->line_bank->setHidden(true);
        ui->label_bank->setHidden(true);

        ui->line_edrpoy->setHidden(true);
        ui->label_edrpoy->setHidden(true);

        ui->line_address->setHidden(true);
        ui->label_address->setHidden(true);

        ui->line_email->setHidden(true);
        ui->label_email->setHidden(true);
    }
    else if(table == Tables::customers)
    {
        ui->line_password->setHidden(true);
        ui->label_password->setHidden(true);
    }
    else
        QMessageBox::critical(nullptr, "Помилка AddPerson", "constructor", QMessageBox::Ok);

    this->adjustSize();


    if(ID == "NULL")
        this->setWindowTitle("Додавання запису");
    else
        this->setWindowTitle("Редагування запису");
}

AddPerson::~AddPerson()
{
    delete ui;
}

void AddPerson::on_btn_add_clicked()
{
    QString name = ui->line_name->text(),
            iban = ui->line_iban->text(),
            bank = ui->line_bank->text(),
            edrpoy = ui->line_edrpoy->text(),
            ipn = ui->line_ipn->text(),
            address = ui->line_address->text(),
            number = ui->line_number->text(),
            email = ui->line_email->text(),
            password = ui->line_password->text(),
            isAdmin = "0";

    // STRICT PARAMS ORDER ACCORDING TO DATABASE TABLES

    //! SET TO ON CONFLICT REPLACE, SO DOESNT MATTER IF EDIT OR ADD
    QStringList requestList = {
        SERVER_API[Api::_add],
        DATABASE_TABLES[table],
        ID,
        "'" + name + "'"
    };

    // if not hidden
    if(!ui->line_iban->isHidden())
        requestList.push_back("'" + iban + "'");

    if(!ui->line_bank->isHidden())
        requestList.push_back("'" + bank + "'");

    if(!ui->line_edrpoy->isHidden())
        requestList.push_back("'" + edrpoy + "'");

    // exist for all
    requestList.push_back("'" + ipn + "'");
    requestList.push_back("'" + address + "'");

    if(!ui->line_number->isHidden())
        requestList.push_back("'" + number + "'");

    if(!ui->line_email->isHidden())
        requestList.push_back("'" + email + "'");

    if(!ui->line_password->isHidden())
        requestList.push_back("'" + password + "'");

    // special for isAdmin
    if(table == Tables::users)
    {
        if(ADMINS_NUMBERS.contains(number))
            isAdmin = "1";
        requestList.push_back(isAdmin);
    }

    // send request
    emit networkCommunication->requestReady(requestList.join(DELIMITERS[Delimiters::primary]));

    // get response
    QString response = networkCommunication->getResponseWhenReady();
    if(response == "-1")
    {
        QMessageBox::critical(nullptr, "Помилка AddPerson", "on_btn_add_clicked", QMessageBox::Ok);
        this->reject();
    }

    this->accept();
}


