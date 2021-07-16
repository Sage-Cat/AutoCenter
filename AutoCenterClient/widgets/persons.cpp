#include "persons.h"
#include "ui_persons.h"

#include <QMessageBox>

#include "dialogs/addperson.h"

Persons::Persons(QWidget *parent, NetworkCommunication *networkCommunication, Tables table) :
    QWidget(parent),
    ui(new Ui::Persons),
    networkCommunication(networkCommunication),
    table(table)
{
    ui->setupUi(this);

    // SET UP GUI
    if(table == Tables::sellers)
    {
        ui->btn_info->setHidden(true);
        ui->btn_cars->setHidden(true);
    }
    else if(table == Tables::users)
        ui->btn_cars->setHidden(true);

    on_btn_refresh_clicked();
}

Persons::~Persons()
{
    delete ui;
}

void Persons::on_btn_add_clicked()
{
    openEditDialog("NULL"); // if add then ID autoincremented
}


void Persons::on_btn_del_clicked()
{
    auto result = QMessageBox::information(nullptr, "Видалення", "Ви впевнені, що хочете видалити цей запис?", QMessageBox::Yes | QMessageBox::No);

    if(result == QMessageBox::Yes)
    {
        auto selectedRows = ui->tableWidget->selectionModel()->selectedRows(COLUMN_ID_INDEX[table]); // taking ID from view
        if(selectedRows.size() < 1)
            return;

        QString ID = selectedRows.at(0).data(Qt::DisplayRole).toString();

        QStringList requestList = {
            SERVER_API[Api::_del],
            DATABASE_TABLES[table], // deleting from table
            "ID=" + ID
        };

        emit networkCommunication->requestReady(requestList.join(DELIMITERS[Delimiters::primary]));

        if(networkCommunication->getResponseWhenReady() != "1")
            QMessageBox::critical(nullptr, "Помилка Persons", "on_btn_del_clicked: Table=" + DATABASE_TABLES[table], QMessageBox::Ok);

        on_btn_refresh_clicked();
    }

}


void Persons::on_btn_refresh_clicked()
{
    // SELECT * FROM view WHERE TRUE
    QStringList requestList = {
        SERVER_API[Api::_get],
        DATABASE_TABLES[table],
        "TRUE"
    };

    emit networkCommunication->requestReady(requestList.join(DELIMITERS[Delimiters::primary]));

    // GET RESPONSE (parsing it to the list of records)
    RecordsList recordsList;
    for(const auto &record : networkCommunication->getResponseWhenReady().split(DELIMITERS[Delimiters::primary]))
        recordsList.push_back(record.split(DELIMITERS[Delimiters::secondary]));

    /* COLUMNS */
    int column_count = COLUMN_NAMES[table].size();

    ui->tableWidget->setColumnCount(column_count);
    ui->tableWidget->setHorizontalHeaderLabels(COLUMN_NAMES[table]);

    // hide ID
    ui->tableWidget->setColumnHidden(COLUMN_ID_INDEX[table], true);

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
            ui->tableWidget->setItem(row, col, new QTableWidgetItem(recordsList[row][col]));

}


void Persons::on_btn_info_clicked()
{
    auto selectedItemsList = ui->tableWidget->selectedItems();

    if(selectedItemsList.size() < 1)
        return;

    int row = selectedItemsList.at(0)->row();
    int selectedID = ui->tableWidget->item(row, COLUMN_ID_INDEX[table])->data(Qt::DisplayRole).toInt();

    if(table == Tables::customers)
        emit tabInfoRequested(Tables::info_customer, selectedID);
    else if(table == Tables::users)
        emit tabInfoRequested(Tables::info_user, selectedID);
}


void Persons::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{
    QString ID = ui->tableWidget->item(item->row(), COLUMN_ID_INDEX[table])->data(Qt::DisplayRole).toString();

    openEditDialog(ID);
}

void Persons::openEditDialog(QString ID)
{
    AddPerson *dlg = new AddPerson(this, networkCommunication, table, ID);
    if(dlg->exec() == QDialog::Accepted)
        on_btn_refresh_clicked();
}


void Persons::on_btn_cars_clicked()
{

}

