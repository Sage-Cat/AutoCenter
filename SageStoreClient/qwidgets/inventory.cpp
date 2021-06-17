#include "inventory.h"
#include "ui_inventory.h"

#include <QMessageBox>

Inventory::Inventory(QWidget *parent, TcpClient *client) :
    QWidget(parent),
    ui(new Ui::Inventory),
    client(client)
{
    ui->setupUi(this);

    on_btn_refresh_clicked();
}

Inventory::~Inventory()
{
    delete ui;
}

void Inventory::on_btn_del_clicked()
{

}

void Inventory::on_btn_refresh_clicked()
{
    recordsList.clear();
    QStringList requestList {
        "get",
        "ProductTypes",
        "Amount>0"
    };

    QString result = client->send_and_get_response(requestList.join(DELIMITER_MAIN));
    if(result != "-1")
    {
        // SAVE records List
        auto list = result.split(DELIMITER_MAIN);
        for(auto str : list)
            recordsList.push_back(str.split(DELIMITER_AUXILIARY));

        // SHOW new recordsList
        ui->table_storage->setColumnCount(INVENTORY_COLUMNS_NAMES.size());
        int rowCount = recordsList.size();
        ui->table_storage->setRowCount(rowCount);
        for(int n = 0; n < rowCount; ++n)
            for(int m = 0; m < recordsList[n].size(); ++m)
                ui->table_storage->setItem(n, m, new QTableWidgetItem(recordsList[n][m]));

        // Cutomization
        ui->table_storage->setHorizontalHeaderLabels(INVENTORY_COLUMNS_NAMES);
        ui->table_storage->setWordWrap(true);

        ui->table_storage->setColumnHidden(1, true);
        ui->table_storage->setColumnHidden(7, true);

        ui->table_storage->setColumnWidth(0, 70);
        ui->table_storage->setColumnWidth(5, 300);
    }
    else
        QMessageBox::critical(this, "Помилка", "Сервер не підвантажує інвентар", QMessageBox::Ok);
}

void Inventory::on_btn_check_clicked()
{

}
