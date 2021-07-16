#include "lists.h"
#include "ui_lists.h"

#include "mainwindow.h"

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
        SERVER_API[Api::_add],
        DATABASE_TABLES[Tables::lists] + "(ID)",
        "NULL"
    };
    // send request
    emit networkCommunication->requestReady(requestList.join(DELIMITERS[Delimiters::primary]));

    // get response
    QString response = networkCommunication->getResponseWhenReady();
    if(response == "-1")
    {
        QMessageBox::critical(nullptr, "Помилка Lists", "on_btn_add_clicked can't and empty record", QMessageBox::Ok);
        return;
    }

    // open records tab
    emit this->tabRecordsRequested(response.toInt(), type);

    // refresh
    on_btn_refresh_clicked();
}

void Lists::on_btn_del_clicked()
{
    auto listOf_selected_IDs = ui->tableWidget->selectionModel()->selectedRows(COLUMN_ID_INDEX[Tables::view_lists]);
    if(listOf_selected_IDs.size() < 1)
        return;
    QString ID_List = listOf_selected_IDs.at(0).data().toString();

    auto result = QMessageBox::information(nullptr, "Видалення", "Ви впевнені, що хочете видалити цей запис?", QMessageBox::Yes | QMessageBox::No);

    if(result == QMessageBox::Yes)
    {
        // del:[table_name]:[condition]
        QStringList requestList = {
            SERVER_API[Api::_del],
            DATABASE_TABLES[Tables::lists],
            "ID=" + ID_List
        };

        // send request
        emit networkCommunication->requestReady(requestList.join(DELIMITERS[Delimiters::primary]));
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
        SERVER_API[Api::_get],
        DATABASE_TABLES[Tables::view_lists],
        condition
    };

    // SEND REQUEST
    emit networkCommunication->requestReady(requestList.join(DELIMITERS[Delimiters::primary]));

    // GET RESPONSE (parsing it to the list of records)
    RecordsList recordsList;
    for(const auto &record : networkCommunication->getResponseWhenReady().split(DELIMITERS[Delimiters::primary]))
        recordsList.push_back(record.split(DELIMITERS[Delimiters::secondary]));

    /* COLUMNS */
    int column_count = COLUMN_NAMES[Tables::view_lists].size();

    ui->tableWidget->setColumnCount(column_count);
    ui->tableWidget->setHorizontalHeaderLabels(COLUMN_NAMES[Tables::view_lists]);

    // hide id and id_list columns
    ui->tableWidget->setColumnHidden(COLUMN_ID_INDEX[Tables::view_lists], true);
    ui->tableWidget->setColumnHidden(VIEW_LISTS_IPN_INDEX, true);

    /* ROWS */
    if(recordsList.size() < 1)
        return;

    if(recordsList.at(0).at(0) == "")
    {
        ui->tableWidget->setRowCount(0);
        return;
    }

    // setting up the data
    int row_count = recordsList.size();
    ui->tableWidget->setRowCount(row_count);
    for(int row = 0; row < row_count; ++row)
        for(int col = 0; col < column_count; ++col)
            if(col == VIEW_LISTS_LISTTYPE_INDEX) // SPECIAL FOR ListType
            {
                ListTypes listType = static_cast<ListTypes>(recordsList[row][col].toInt());
                if(listType < LIST_TYPES.size())
                    ui->tableWidget->setItem(row, col, new QTableWidgetItem(LIST_TYPES[listType]));
            }
            else
                ui->tableWidget->setItem(row, col, new QTableWidgetItem(recordsList[row][col]));
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

void Lists::on_tableWidget_cellDoubleClicked(int row, int)
{
    int ID_List = ui->tableWidget->item(row, COLUMN_ID_INDEX[Tables::view_lists])->data(Qt::DisplayRole).toInt();

    // open records tab
    emit tabRecordsRequested(ID_List, type);
}

