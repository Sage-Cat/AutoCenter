#include "lists.h"
#include "ui_lists.h"

Lists::Lists(QWidget *parent, NetworkCommunication* networkCommunication, OperationType type) :
    QWidget(parent),
    ui(new Ui::Lists),
    networkCommunication(networkCommunication),
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
    // INSERT INTO Lists(ID_List) VALUES(NULL)
    QStringList requestList = {
        SERVER_API[ServerAPI::records_add],
        DATABASE_TABLES[Tables::lists] + "(ID)",
        "NULL"
    };
    // send request
    emit networkCommunication->requestReady(requestList.join(DELIMITERS[delims::primary]));

    // get response
    QString response = networkCommunication->getResponseWhenReady();
    if(response == "-1")
    {
        QMessageBox::critical(nullptr, "Помилка Lists", "on_btn_add_clicked can't and empty record", QMessageBox::Ok);
        return;
    }

    // open records tab
    emit tabRecordsRequested(response.toInt());

    // refresh
    on_btn_refresh_clicked();
}

void Lists::on_btn_del_clicked()
{
    auto listOf_selected_IDs = ui->tableWidget->selectionModel()->selectedRows(VIEW_LISTS_ID_INDEX);
    if(listOf_selected_IDs.size() < 1)
        return;
    QString ID_List = listOf_selected_IDs.at(0).data().toString();

    auto result = QMessageBox::information(nullptr, "Видалення", "Ви впевнені, що хочете видалити цей запис?", QMessageBox::Yes | QMessageBox::No);

    if(result == QMessageBox::Yes)
    {
        // del:[table_name]:[condition]
        QStringList requestList = {
            SERVER_API[ServerAPI::records_delete],
            DATABASE_TABLES[Tables::lists],
            "ID=" + ID_List
        };

        // send request
        emit networkCommunication->requestReady(requestList.join(DELIMITERS[delims::primary]));
        // get response
        if(networkCommunication->getResponseWhenReady() != "1")
            QMessageBox::critical(nullptr, "Помилка Lists", "on_btn_del_clicked can't delete record", QMessageBox::Ok);

        // refresh
        on_btn_refresh_clicked();
    }
}

void Lists::on_btn_refresh_clicked()
{
    // get:[table_name or view_name]:[condition]

    QString condition = "";
    if(type == OperationType::sale)
    {
        condition = "ListType<>5 OR ListType IS NULL"; // ALL except receipts
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
        DATABASE_TABLES[Tables::lists_view],
        condition
    };

    // SEND REQUEST
    emit networkCommunication->requestReady(requestList.join(DELIMITERS[delims::primary]));

    // GET RESPONSE (parsing it to the list of records)
    RecordsList recordsList;
    for(const auto &record : networkCommunication->getResponseWhenReady().split(DELIMITERS[delims::primary]))
        recordsList.push_back(record.split(DELIMITERS[delims::secondary]));

    // seting up the tableWidget
    if(recordsList.size() < 1)
        return;

    int row_count = recordsList.size();
    int column_count = recordsList.at(0).size();

    // setting up the data
    ui->tableWidget->setRowCount(row_count);
    ui->tableWidget->setColumnCount(column_count);
    for(int row = 0; row < row_count; ++row)
        for(int col = 0; col < column_count; ++col)
            if(col == 2) // SPECIAL FOR ListType
            {
                qsizetype listType = recordsList[row][col].toUInt();
                if(listType < LISTTYPE_NAMES.size())
                    ui->tableWidget->setItem(row, col, new QTableWidgetItem(LISTTYPE_NAMES[listType]));
            }
            else
                ui->tableWidget->setItem(row, col, new QTableWidgetItem(recordsList[row][col]));

    ui->tableWidget->setHorizontalHeaderLabels(LISTS_COLUMNS_NAMES);

    ui->tableWidget->setColumnHidden(VIEW_LISTS_ID_INDEX, true); // hide ID column
    ui->tableWidget->setColumnHidden(VIEW_LISTS_IPN_INDEX, true); // hide IPN column
}

void Lists::on_radio_all_clicked()
{
    for(int row = 0; row < ui->tableWidget->rowCount(); ++row)
        ui->tableWidget->setRowHidden(row, false);
}

void Lists::on_radio_org_clicked()
{
    for(int row = 0; row < ui->tableWidget->rowCount(); ++row)
        if(ui->tableWidget->item(row, VIEW_LISTS_IPN_INDEX)->data(Qt::DisplayRole) != "")
            ui->tableWidget->setRowHidden(row, false);
        else
            ui->tableWidget->setRowHidden(row, true);
}

void Lists::on_radio_not_org_clicked()
{
    for(int row = 0; row < ui->tableWidget->rowCount(); ++row)
        if(ui->tableWidget->item(row, VIEW_LISTS_IPN_INDEX)->data(Qt::DisplayRole) == "")
            ui->tableWidget->setRowHidden(row, false);
        else
            ui->tableWidget->setRowHidden(row, true);
}

void Lists::on_tableWidget_cellDoubleClicked(int row, int column)
{
    int ID_List = ui->tableWidget->item(row, VIEW_LISTS_ID_INDEX)->data(Qt::DisplayRole).toInt();

    // open records tab
    emit tabRecordsRequested(ID_List);
}

