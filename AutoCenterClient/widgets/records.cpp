#include "records.h"
#include "ui_records.h"

#include <QVector>

Records::Records(QWidget *parent, NetworkCommunication *networkCommunication, int ID_List) :
    QWidget(parent),
    ui(new Ui::Records),
    networkCommunication(networkCommunication),
    ID_List(ID_List),
    ignore_combobox_index_changing(true),
    ignore_tableWidget_cells_changing(true)
{
    ui->setupUi(this);

    // set gui
    init_graphical_widgets();
    ignore_combobox_index_changing = false;
}

Records::~Records()
{
    delete ui;
}

void Records::on_comboBox_Customer_currentIndexChanged(int index)
{
    if(!ignore_combobox_index_changing)
    {
        // edit:[table_name]:[condition]:[data1:data2:...]

        // UPDATE Lists SET ID_Customer=index  WHERE ID=ID_List
        QStringList requestList = {
            SERVER_API[ServerAPI::records_edit],
            DATABASE_TABLES[Tables::lists],
            "ID=" + QString::number(ID_List),
            "ID_Customer=" + QString::number(customers_indexToID[index])
        };

        emit networkCommunication->requestReady(requestList.join(DELIMITERS[delims::primary]));

        if(networkCommunication->getResponseWhenReady() != "1")
            QMessageBox::critical(nullptr, "Помилка Records", "on_comboBox_Customer_currentIndexChanged", QMessageBox::Ok);
    }
}

void Records::on_comboBox_Seller_currentIndexChanged(int index)
{
    if(!ignore_combobox_index_changing)
    {
        // UPDATE Lists SET ID_Seller=index  WHERE ID=ID_List
        QStringList requestList = {
            SERVER_API[ServerAPI::records_edit],
            DATABASE_TABLES[Tables::lists],
            "ID=" + QString::number(ID_List),
            "ID_Seller=" + QString::number(sellers_indexToID[index])
        };

        emit networkCommunication->requestReady(requestList.join(DELIMITERS[delims::primary]));

        if(networkCommunication->getResponseWhenReady() != "1")
            QMessageBox::critical(nullptr, "Помилка Records", "on_comboBox_Seller_currentIndexChanged", QMessageBox::Ok);
    }
}

void Records::init_graphical_widgets()
{
    // SELECT * FROM Lists WHERE ID=ID_List
    QStringList requestList = {
        SERVER_API[ServerAPI::records_get],
        DATABASE_TABLES[Tables::lists],
        "ID=" + QString::number(ID_List)
    };
    emit networkCommunication->requestReady(requestList.join(DELIMITERS[delims::primary]));

    QStringList record = networkCommunication->getResponseWhenReady().split(DELIMITERS[delims::secondary]);

    /* SETUP widgets */

    // set datetime
    ui->line_datetime->setText(record.at(TABLE_LISTS_DATETIME_INDEX));

    // set comboboxes
    QStringList sellers(getAllSellersNames_and_setIndexToID());
    ui->comboBox_Seller->addItems(sellers);
    ui->comboBox_Seller->setCurrentIndex(
                sellers_indexToID.indexOf(record.at(TABLE_LISTS_SELLER_INDEX).toInt())
            );

    QStringList customers(getAllCustomersNames_and_setIndexToID());
    ui->comboBox_Customer->addItems(customers);
    ui->comboBox_Customer->setCurrentIndex(
                customers_indexToID.indexOf(record.at(TABLE_LISTS_CUSTOMER_INDEX).toInt())
                );

    // set tableWidget & set line_sum
    on_btn_refresh_clicked();
}

void Records::update_line_sum()
{
    QVector<int> counts;
    double sum = 0.0;
    for(int row = 0; row < ui->tableWidget->rowCount(); ++row)
        counts.push_back(ui->tableWidget->item(row, VIEW_RECORDS_COUNT_INDEX)->data(Qt::DisplayRole).toInt());

    for(int row = 0; row < ui->tableWidget->rowCount(); ++row)
        sum += counts[row] * ui->tableWidget->item(row, VIEW_RECORDS_PRICE_INDEX)->data(Qt::DisplayRole).toDouble();

    ui->line_sum->setText(QString::number(sum, 'f', 2));
}

void Records::edit_cell(int row, QString data)
{
    QStringList requestList = {
        SERVER_API[ServerAPI::records_edit],
        DATABASE_TABLES[Tables::records],
        "ID=" + ui->tableWidget->item(row, VIEW_RECORDS_ID_INDEX)->data(Qt::DisplayRole).toString(),
        data
    };

    emit networkCommunication->requestReady(requestList.join(DELIMITERS[delims::primary]));

    if(networkCommunication->getResponseWhenReady() != "1")
        QMessageBox::critical(nullptr, "Помилка Records", "on_tableWidget_itemChanged Count", QMessageBox::Ok);
}

QString Records::find_ID_ProductType_by_Code(QString code)
{
    QStringList requestList = {
        SERVER_API[ServerAPI::records_get],
        DATABASE_TABLES[Tables::product_types],
        "Code='" + code + "'"
    };

    emit networkCommunication->requestReady(requestList.join(DELIMITERS[delims::primary]));

    QString response = networkCommunication->getResponseWhenReady();

    return response.split(DELIMITERS[delims::secondary]).at(TABLE_PRODUCTTYPES_ID_INDEX);
}

QStringList Records::getAllCustomersNames_and_setIndexToID()
{
    // SELECT * FROM Customers WHERE TRUE
    QStringList requestList = {
        SERVER_API[ServerAPI::records_get],
        DATABASE_TABLES[Tables::customers],
        "TRUE"
    };
    emit networkCommunication->requestReady(requestList.join(DELIMITERS[delims::primary]));

    customers_indexToID.clear();

    QStringList listOf_Customers_Names;
    for(const auto &record : networkCommunication->getResponseWhenReady().split(DELIMITERS[delims::primary]))
    {
        QStringList row = record.split(DELIMITERS[delims::secondary]);
        listOf_Customers_Names << row.at(TABLE_CUSTOMERS_NAMES_INDEX);
        customers_indexToID.push_back(row.at(TABLE_CUSTOMERS_ID_INDEX).toInt());
    }

    return listOf_Customers_Names;
}

QStringList Records::getAllSellersNames_and_setIndexToID()
{
    // SELECT * FROM Customers WHERE TRUE
    QStringList requestList = {
        SERVER_API[ServerAPI::records_get],
        DATABASE_TABLES[Tables::sellers],
        "TRUE"
    };
    emit networkCommunication->requestReady(requestList.join(DELIMITERS[delims::primary]));

    sellers_indexToID.clear();

    QStringList listOf_Sellers_Names;
    for(const auto &record : networkCommunication->getResponseWhenReady().split(DELIMITERS[delims::primary]))
    {
        QStringList row = record.split(DELIMITERS[delims::secondary]);
        listOf_Sellers_Names << row.at(TABLE_SELLERS_NAMES_INDEX);
        sellers_indexToID.push_back(row.at(TABLE_SELLERS_ID_INDEX).toInt());
    }

    return listOf_Sellers_Names;
}

void Records::on_btn_refresh_clicked()
{
    ignore_tableWidget_cells_changing = true;

    // SELECT * FROM Records WHERE ID_List=ID_List
    QStringList requestList = {
        SERVER_API[ServerAPI::records_get],
        DATABASE_TABLES[Tables::records_view],
        "ID_List=" + QString::number(ID_List)
    };
    // SEND REQUEST
    emit networkCommunication->requestReady(requestList.join(DELIMITERS[delims::primary]));

    // GET RESPONSE (parsing it to the list of records)
    RecordsList recordsList;
    for(const auto &record : networkCommunication->getResponseWhenReady().split(DELIMITERS[delims::primary]))
        recordsList.push_back(record.split(DELIMITERS[delims::secondary]));

    /* COLUMNS */
    int column_count = RECORDS_COLUMNS_NAMES.size();

    ui->tableWidget->setColumnCount(column_count);
    ui->tableWidget->setHorizontalHeaderLabels(RECORDS_COLUMNS_NAMES);

    // hide id and id_list columns
    ui->tableWidget->setColumnHidden(VIEW_RECORDS_IDLIST_INDEX, true);
    ui->tableWidget->setColumnHidden(VIEW_RECORDS_ID_INDEX, true);

    /* ROWS */
    if(recordsList.size() < 1)
        return;

    int row_count = recordsList.size();
    ui->tableWidget->setRowCount(row_count);

    if(recordsList.size() == 1 && recordsList.at(0).at(0) == "")
        return;

    // setting up the data
    for(int row = 0; row < row_count; ++row)
        for(int col = 0; col < column_count; ++col)
            ui->tableWidget->setItem(row, col, new QTableWidgetItem(recordsList[row][col]));

    // update line_sum
    update_line_sum();

    ignore_tableWidget_cells_changing = false;
}

void Records::on_btn_add_clicked()
{
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
}

void Records::on_btn_del_clicked()
{
    auto all_selected_IDs = ui->tableWidget->selectionModel()->selectedRows(VIEW_RECORDS_ID_INDEX);
    if(all_selected_IDs.size() < 1)
        return;

    QString selected_ID = all_selected_IDs.at(0).data(Qt::DisplayRole).toString();

    // DELETE FROM Records WHERE ID=selected_ID
    QStringList requestList = {
        SERVER_API[ServerAPI::records_delete],
        DATABASE_TABLES[Tables::records],
        "ID=" + selected_ID
    };

    emit networkCommunication->requestReady(requestList.join(DELIMITERS[delims::primary]));

    if(networkCommunication->getResponseWhenReady() != "1")
        QMessageBox::critical(nullptr, "Помилка Records", "on_btn_del_clicked", QMessageBox::Ok);

    on_btn_refresh_clicked();
}

void Records::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    if(!ignore_tableWidget_cells_changing)
    {
        int column = item->column();
        if(column == VIEW_RECORDS_CODE_INDEX ||
           column == VIEW_RECORDS_COUNT_INDEX ||
           column == VIEW_RECORDS_PRICE_INDEX
           )
        {
            switch (column) {
                /* CODE COLUMN */
                case VIEW_RECORDS_CODE_INDEX:
                {
                    QString ID_ProductType = find_ID_ProductType_by_Code(item->data(Qt::DisplayRole).toString());

                    if(ID_ProductType != "")
                    {
                        edit_cell(item->row(), "ID_ProductType=" + ID_ProductType);
                    }
                    // IF THERE IS NO SUCH PRODUCT 'CREATE NEW?'
                    else
                    {
                    /* ------------ TODO CREATING NEW ProductType ----------- */
                    }
                } break;

                /* COUNT COLUMN */
                case VIEW_RECORDS_COUNT_INDEX:
                {
                    edit_cell(item->row(), "Count=" + item->data(Qt::DisplayRole).toString());
                } break;

                /* PRICE COLUMN */
                case VIEW_RECORDS_PRICE_INDEX:
                {
                    edit_cell(item->row(), "Price=" + item->data(Qt::DisplayRole).toString());
                } break;

            }

            // update tableWidget and line_sum
            on_btn_refresh_clicked();
            update_line_sum();
        }
    }
}

