#include "sellers.h"
#include "ui_sellers.h"

#include "qdialogs/new_seller.h"

#include <QMessageBox>

#include "statements.h"

Sellers::Sellers(QWidget *parent, TcpClient *client) :
    QWidget(parent),
    ui(new Ui::Sellers),
    client(client)
{
    ui->setupUi(this);

    // load table data
    on_btn_refresh_clicked();
}

Sellers::~Sellers()
{
    delete ui;
}

void Sellers::on_btn_add_clicked()
{
    New_seller *dlg = new New_seller(this, client);
    if(dlg->exec() == QDialog::Accepted)
        on_btn_refresh_clicked();
}

void Sellers::on_btn_del_clicked()
{

}

void Sellers::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{

}

void Sellers::on_btn_refresh_clicked()
{
    //clear previous data
    recordsList.clear();

    // get data from server
    QStringList requestList = {"get", "Sellers", "TRUE"};
    QString result = client->send_and_get_response(requestList.join(DELIMITER_MAIN));

    if(result != "-1")
    {
        // SAVE records List
        auto list = result.split(DELIMITER_MAIN);
        for(auto str : list)
            recordsList.push_back(str.split(DELIMITER_AUXILIARY));

        // SHOW new recordsList
        ui->tableWidget->setColumnCount(SELLERS_COLUMNS_COUNT);
        int rowCount = recordsList.size();
        ui->tableWidget->setRowCount(rowCount);
        for(int n = 0; n < rowCount; ++n)
            for(int m = 0; m < recordsList[n].size(); ++m)
                ui->tableWidget->setItem(n, m, new QTableWidgetItem(recordsList[n][m]));

        // Cutomization
        ui->tableWidget->setHorizontalHeaderLabels(SELLERS_COLUMNS_NAMES);
        ui->tableWidget->setWordWrap(true);
    }
    else
        QMessageBox::critical(this, "Помилка", "Сервер не підвантажує продавців", QMessageBox::Ok);
}
