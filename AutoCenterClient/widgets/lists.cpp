#include "lists.h"
#include "ui_lists.h"

Lists::Lists(QWidget *parent, TcpClient* tcpClient, OperationType type) :
    QWidget(parent),
    ui(new Ui::Lists),
    type(type),
    networkCommunication(new NetworkCommunication(tcpClient))
{
    ui->setupUi(this);

    // load data
    on_btn_refresh_clicked();
}

Lists::~Lists()
{
    delete ui;
}

void Lists::on_btn_add_clicked()
{

}

void Lists::on_btn_del_clicked()
{

}

void Lists::on_btn_refresh_clicked()
{
    // get:[table_name or view_name]:[condition]

    QString condition = "";
    if(type == OperationType::sale)
    {
        condition = "IS NOT ListType=5"; // ALL except receipts
    }
    else if(type == OperationType::receipt)
    {
        condition = "ListType=5"; // ONLY receipts
    }
    else
    {
        QMessageBox::critical(nullptr, "Помилка Lists", "on_btn_refresh_clicked unknown OperationType", QMessageBox::Ok);
        return;
    }

    QStringList requestList = {
        TABLE_LISTS_NAME,
        condition
    };
    emit networkCommunication->requestReady(requestList.join(DELIMITERS[delims::primary]));
}

void Lists::on_radio_all_clicked()
{

}

void Lists::on_radio_org_clicked()
{

}

void Lists::on_radio_not_org_clicked()
{

}
