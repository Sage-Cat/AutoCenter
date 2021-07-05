#include "lists.h"
#include "ui_lists.h"

Lists::Lists(QWidget *parent, TcpClient* tcpClient, OperationType type) :
    QWidget(parent),
    ui(new Ui::Lists),
    networkCommunication(new NetworkCommunication(tcpClient)),
    type(type)
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
        condition = "ListType<>5"; // ALL except receipts
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
        SERVER_API[ServerAPI::records_get],
        TABLE_LISTS_NAME,
        condition
    };

    // SEND REQUEST
    emit networkCommunication->requestReady(requestList.join(DELIMITERS[delims::primary]));

    // GET RESPONSE (parsing it to the list of records
    RecordsList recordsList;
    for(auto record : networkCommunication->getResponseWhenReady().split(DELIMITERS[delims::primary]))
        recordsList.push_back(record.split(DELIMITERS[delims::secondary]));

    // seting up the tableWidget
    ui->tableWidget->setColumnCount(TABLE_LISTS_COLUMNS_NAMES.size());
    ui->tableWidget->setHorizontalHeaderLabels(TABLE_LISTS_COLUMNS_NAMES);

    if(recordsList.size() < 1)
        return;

    ui->tableWidget->setRowCount(recordsList.size());
    for(size_t row = 0; row < recordsList.size(); ++row)
        for(size_t col = 0; col < recordsList.at(0).size(); ++col)
            ui->tableWidget->setItem(row, col, new QTableWidgetItem(recordsList[row][col]));
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
