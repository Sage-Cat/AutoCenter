#include "customers.h"
#include "ui_customers.h"

#include <QMessageBox>

#include "statements.h"
#include "qdialogs/new_customer.h"

Customers::Customers(QWidget *parent, TcpClient *client) :
    QWidget(parent),
    ui(new Ui::Customers),
    client(client)
{
    ui->setupUi(this);

    // load table data
    on_btn_refresh_clicked();
}

Customers::~Customers()
{
    delete ui;
}

void Customers::on_btn_add_clicked()
{
    New_customer *dlg = new New_customer(this, client);
    if(dlg->exec() == QDialog::Accepted)
        on_btn_refresh_clicked();
}

void Customers::on_btn_del_clicked()
{

}

void Customers::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{

}

void Customers::on_btn_info_clicked()
{

}

void Customers::on_btn_refresh_clicked()
{
    //clear previous data
    recordsList.clear();

    // get data from server
    QStringList requestList = {"get", "Customers", "TRUE"};
    QString result = client->send_and_get_response(requestList.join(DELIMITER_MAIN));

    if(result != "-1")
    {
        // SAVE records List
        auto list = result.split(DELIMITER_MAIN);
        for(auto str : list)
            recordsList.push_back(str.split(DELIMITER_AUXILIARY));

        // SHOW new recordsList
        ui->tableWidget->setColumnCount(CUSTOMERS_COLUMNS_COUNT);
        int rowCount = recordsList.size();
        ui->tableWidget->setRowCount(rowCount);
        for(int n = 0; n < rowCount; ++n)
            for(int m = 0; m < recordsList[n].size(); ++m)
                ui->tableWidget->setItem(n, m, new QTableWidgetItem(recordsList[n][m]));

        // Cutomization
        ui->tableWidget->setHorizontalHeaderLabels(CUSTOMERS_COLUMNS_NAMES);
        ui->tableWidget->setWordWrap(true);
    }
    else
        QMessageBox::critical(this, "Помилка", "Сервер не підвантажує покупців", QMessageBox::Ok);
}
