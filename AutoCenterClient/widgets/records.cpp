#include "records.h"
#include "ui_records.h"

#include <QVector>

#include "dialogs/changelisttype.h"
#include "dialogs/addproduct.h"

Records::Records(QWidget *parent, NetworkCommunication *networkCommunication, int ID_List, OperationType type) :
    QWidget(parent),
    ui(new Ui::Records),
    networkCommunication(networkCommunication),
    ID_List(ID_List),
    operationType(type),
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
            SERVER_API[Api::_edit],
            DATABASE_TABLES[Tables::lists],
            "ID=" + QString::number(ID_List),
            "ID_Customer=" + QString::number(customers_indexToID[index])
        };

        emit networkCommunication->requestReady(requestList.join(DELIMITERS[Delimiters::primary]));

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
            SERVER_API[Api::_edit],
            DATABASE_TABLES[Tables::lists],
            "ID=" + QString::number(ID_List),
            "ID_Seller=" + QString::number(sellers_indexToID[index])
        };

        emit networkCommunication->requestReady(requestList.join(DELIMITERS[Delimiters::primary]));

        if(networkCommunication->getResponseWhenReady() != "1")
            QMessageBox::critical(nullptr, "Помилка Records", "on_comboBox_Seller_currentIndexChanged", QMessageBox::Ok);
    }
}

void Records::on_btn_add_clicked()
{
    ignore_tableWidget_cells_changing = true;

    int newRow_index = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(newRow_index + 1);
    for(int column = 0; column < ui->tableWidget->columnCount(); ++column)
        ui->tableWidget->setItem(newRow_index, column, new QTableWidgetItem(""));

    ignore_tableWidget_cells_changing = false;
}

void Records::on_btn_del_clicked()
{
    auto all_selected_IDs = ui->tableWidget->selectionModel()->selectedRows(COLUMN_ID_INDEX[Tables::view_records]);
    if(all_selected_IDs.size() < 1)
        return;

    QString selected_ID = all_selected_IDs.at(0).data(Qt::DisplayRole).toString();

    // DELETE FROM Records WHERE ID=selected_ID
    QStringList requestList = {
        SERVER_API[Api::_del],
        DATABASE_TABLES[Tables::records],
        "ID=" + selected_ID
    };

    emit networkCommunication->requestReady(requestList.join(DELIMITERS[Delimiters::primary]));

    if(networkCommunication->getResponseWhenReady() != "1")
        QMessageBox::critical(nullptr, "Помилка Records", "on_btn_del_clicked", QMessageBox::Ok);

    on_btn_refresh_clicked();
}

void Records::on_btn_refresh_clicked()
{
    ignore_tableWidget_cells_changing = true;

    // SELECT * FROM Records WHERE ID_List=ID_List
    QStringList requestList = {
        SERVER_API[Api::_get],
        DATABASE_TABLES[Tables::view_records],
        "ID_List=" + QString::number(ID_List)
    };
    // SEND REQUEST
    emit networkCommunication->requestReady(requestList.join(DELIMITERS[Delimiters::primary]));

    // GET RESPONSE (parsing it to the list of records)
    RecordsList recordsList;
    for(const auto &record : networkCommunication->getResponseWhenReady().split(DELIMITERS[Delimiters::primary]))
        recordsList.push_back(record.split(DELIMITERS[Delimiters::secondary]));

    /* COLUMNS */
    int column_count = COLUMN_NAMES[Tables::view_records].size();

    ui->tableWidget->setColumnCount(column_count);
    ui->tableWidget->setHorizontalHeaderLabels(COLUMN_NAMES[Tables::view_records]);

    // hide special columns
    ui->tableWidget->setColumnHidden(VIEW_IDLIST_INDEX, true);
    ui->tableWidget->setColumnHidden(COLUMN_ID_INDEX[Tables::view_records], true);
    ui->tableWidget->setColumnHidden(VIEW_IDPRODUCT_INDEX, true);

    /* ROWS */
    if(recordsList.size() < 1)
        return;

    int row_count = recordsList.size();
    ui->tableWidget->setRowCount(row_count);

    if(recordsList.size() == 1 && recordsList.at(0).at(0) == "")
    {
        ui->tableWidget->setRowCount(0);
        return;
    }

    // setting up the data
    for(int row = 0; row < row_count; ++row)
        for(int col = 0; col < column_count; ++col)
            ui->tableWidget->setItem(row, col, new QTableWidgetItem(recordsList[row][col]));

    // update line_sum
    update_line_sum();

    ignore_tableWidget_cells_changing = false;
}

void Records::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    if(!ignore_tableWidget_cells_changing)
    {
        int row = item->row();
        int column = item->column();
        QString data = item->data(Qt::DisplayRole).toString();

        if(ui->tableWidget->item(row, COLUMN_ID_INDEX[Tables::view_records])->data(Qt::DisplayRole).toString() != "")
            handleChangingForExistingRow(row, column, data);
        else
            handleChangingForNonExistingRow(column, data);
    }
}

void Records::on_btn_print_barcode_clicked()
{

}

void Records::on_btn_print_document_clicked()
{
    ChangeListType *dlg = new ChangeListType;
    connect(dlg, &ChangeListType::typeSelected, this, &Records::changeListType);

    if(dlg->exec() == QDialog::Accepted)
    {
        // TODO PRINT DOCUMENT
    }
}

void Records::changeListType(int type_index)
{
    QStringList requestList = {
        SERVER_API[Api::_edit],
        DATABASE_TABLES[Tables::lists],
        "ID=" + QString::number(ID_List),
        "ListType=" + QString::number(type_index)
    };

    emit networkCommunication->requestReady(requestList.join(DELIMITERS[Delimiters::primary]));

    if(networkCommunication->getResponseWhenReady() != "1")
        QMessageBox::critical(nullptr, "Помилка Records", "changeListType", QMessageBox::Ok);

    // SETTING new ListNumber
    changeListNumber(getNextNumberforListType(type_index));
}

QStringList Records::getAllCustomersNames_and_setIndexToID()
{
    // SELECT * FROM Customers WHERE TRUE
    QStringList requestList = {
        SERVER_API[Api::_get],
        DATABASE_TABLES[Tables::customers],
        "TRUE"
    };
    emit networkCommunication->requestReady(requestList.join(DELIMITERS[Delimiters::primary]));

    customers_indexToID.clear();

    QStringList listOf_Customers_Names;
    for(const auto &record : networkCommunication->getResponseWhenReady().split(DELIMITERS[Delimiters::primary]))
    {
        if(record != "")
        {
            QStringList row = record.split(DELIMITERS[Delimiters::secondary]);
            listOf_Customers_Names << row.at(TABLE_CUSTOMERS_NAMES_INDEX);
            customers_indexToID.push_back(row.at(COLUMN_ID_INDEX[Tables::customers]).toInt());
        }
        else
        {
            listOf_Customers_Names << "";
            customers_indexToID.push_back(ERROR_CODE);
        }
    }

    return listOf_Customers_Names;
}

QStringList Records::getAllSellersNames_and_setIndexToID()
{
    // SELECT * FROM Customers WHERE TRUE
    QStringList requestList = {
        SERVER_API[Api::_get],
        DATABASE_TABLES[Tables::sellers],
        "TRUE"
    };
    emit networkCommunication->requestReady(requestList.join(DELIMITERS[Delimiters::primary]));

    sellers_indexToID.clear();

    QStringList listOf_Sellers_Names;
    for(const auto &record : networkCommunication->getResponseWhenReady().split(DELIMITERS[Delimiters::primary]))
    {
        if(record != "")
        {
            QStringList row = record.split(DELIMITERS[Delimiters::secondary]);
            listOf_Sellers_Names << row.at(TABLE_SELLERS_NAMES_INDEX);
            sellers_indexToID.push_back(row.at(COLUMN_ID_INDEX[Tables::sellers]).toInt());
        }
        else
        {
            listOf_Sellers_Names << "";
            sellers_indexToID.push_back(ERROR_CODE);
        }
    }

    return listOf_Sellers_Names;
}

void Records::init_graphical_widgets()
{
    // SELECT * FROM Lists WHERE ID=ID_List
    QStringList requestList = {
        SERVER_API[Api::_get],
        DATABASE_TABLES[Tables::lists],
        "ID=" + QString::number(ID_List)
    };
    emit networkCommunication->requestReady(requestList.join(DELIMITERS[Delimiters::primary]));

    QStringList record = networkCommunication->getResponseWhenReady().split(DELIMITERS[Delimiters::secondary]);

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
        counts.push_back(ui->tableWidget->item(row, VIEW_COUNT_INDEX)->data(Qt::DisplayRole).toInt());

    for(int row = 0; row < ui->tableWidget->rowCount(); ++row)
        sum += counts[row] * ui->tableWidget->item(row, VIEW_PRICE_INDEX)->data(Qt::DisplayRole).toDouble();

    ui->line_sum->setText(QString::number(sum, 'f', 2));
}

void Records::changeListNumber(int number)
{
    QStringList requestList = {
        SERVER_API[Api::_edit],
        DATABASE_TABLES[Tables::lists],
        "ID=" + QString::number(ID_List),
        "ListNumber=" + QString::number(number)
    };

    emit networkCommunication->requestReady(requestList.join(DELIMITERS[Delimiters::primary]));

    if(networkCommunication->getResponseWhenReady() != "1")
        QMessageBox::critical(nullptr, "Помилка Records", "changeListNumber", QMessageBox::Ok);
}

void Records::handleChangingForExistingRow(int row, int column, QString data)
{
    if(column == VIEW_CODE_INDEX ||
       column == VIEW_COUNT_INDEX ||
       column == VIEW_PRICE_INDEX
       )
    {
        switch (column) {
            /* CODE COLUMN */
            case VIEW_CODE_INDEX:
            {
                QString ID_Product = find_IDProduct_by_Code(data);

                if(ID_Product != "")
                {
                    edit_cell(row, "ID_Product=" + ID_Product);
                }
                // IF THERE IS NO SUCH PRODUCT THEN 'CREATE NEW?'
                else
                {
                    /* ------------ CREATING Product AND ADDING TO DB NEW Record ----------- */

                    QString ID_Product = createNewProduct();

                    if(ID_Product != "-1")
                        addNewRecordToDB(ID_Product);
                    else
                        QMessageBox::critical(nullptr, "Помилка Records", "handleChangingForExistingRow", QMessageBox::Ok);

                }
            } break;

            /* COUNT COLUMN */
            case VIEW_COUNT_INDEX:
            {
                edit_cell(row, "Count=" + data);
            } break;

            /* PRICE COLUMN */
            case VIEW_PRICE_INDEX:
            {
                edit_cell(row, "Price=" + data);
            } break;

        }

        // update tableWidget and line_sum
        on_btn_refresh_clicked();
        update_line_sum();
    }
}

void Records::handleChangingForNonExistingRow(int column, QString data)
{
    if(column == VIEW_CODE_INDEX)
    {
        // getting data
        QString ID_Product = find_IDProduct_by_Code(data);

        if(ID_Product != "")
        {
            addNewRecordToDB(ID_Product);
        }
        // IF THERE IS NO SUCH PRODUCT THEN 'CREATE NEW?'
        else
        {
            auto answer = QMessageBox::information(this, "Створення", "Створити новий вид товару?", QMessageBox::Yes | QMessageBox::No);

            if(answer == QMessageBox::Yes)
            {
                /* ------------ CREATING Product AND ADDING TO DB NEW Record ----------- */

                QString ID_Product = createNewProduct();

                if(ID_Product != "-1")
                    addNewRecordToDB(ID_Product);
                else
                    QMessageBox::critical(nullptr, "Помилка Records", "handleChangingForNonExistingRow", QMessageBox::Ok);
            }
        }

        // updating table
        on_btn_refresh_clicked();
    }
}

void Records::edit_cell(int row, QString data)
{
    QStringList requestList = {
        SERVER_API[Api::_edit],
        DATABASE_TABLES[Tables::records],
        "ID=" + ui->tableWidget->item(row, COLUMN_ID_INDEX[Tables::view_records])->data(Qt::DisplayRole).toString(),
        data
    };

    emit networkCommunication->requestReady(requestList.join(DELIMITERS[Delimiters::primary]));

    if(networkCommunication->getResponseWhenReady() != "1")
        QMessageBox::critical(nullptr, "Помилка Records", "edit_cell - " + data, QMessageBox::Ok);
}

QString Records::find_IDProduct_by_Code(QString code)
{
    QStringList requestList = {
        SERVER_API[Api::_get],
        DATABASE_TABLES[Tables::products],
        "Code='" + code + "'"
    };

    emit networkCommunication->requestReady(requestList.join(DELIMITERS[Delimiters::primary]));

    QString response = networkCommunication->getResponseWhenReady();

    return response.split(DELIMITERS[Delimiters::secondary]).at(COLUMN_ID_INDEX[Tables::products]);
}

int Records::getNextNumberforListType(int type_index)
{
    // SELECT * FROM Max_ListNumber
    QStringList requestList = {
        SERVER_API[Api::_get],
        DATABASE_TABLES[Tables::max_list_number],
        "ListType=" + QString::number(type_index)
    };

    emit networkCommunication->requestReady(requestList.join(DELIMITERS[Delimiters::primary]));

    QString response = networkCommunication->getResponseWhenReady();

    if(response == "")
        QMessageBox::critical(nullptr, "Помилка Records", "changeListNumber", QMessageBox::Ok);

    QString number = response.split(DELIMITERS[Delimiters::primary]).at(0);

    return number.toInt() + 1;
}

QString Records::createNewProduct()
{
    AddProduct *dlg = new AddProduct(this, networkCommunication);
    if(dlg->exec() == QDialog::Accepted)
        return dlg->getID_Product();
    else
        return "-1";
}

bool Records::addNewRecordToDB(QString ID_Product)
{
    // INSERT INTO Records(ID, ID_List, ID_Product) VALUES(NULL, 2, 3);
    QStringList requestList = {
        SERVER_API[Api::_add],
        DATABASE_TABLES[Tables::records] + "(ID, ID_List, ID_Product, Count, Price)",
        "NULL", // autoincremented
        QString::number(ID_List),
        ID_Product,
        "0",
        "0.0"
    };

    emit networkCommunication->requestReady(requestList.join(DELIMITERS[Delimiters::primary]));

    if(networkCommunication->getResponseWhenReady() == "-1")
    {
        QMessageBox::critical(nullptr, "Помилка Records", "addNewRecord", QMessageBox::Ok);
        return false;
    }

    return true;
}


