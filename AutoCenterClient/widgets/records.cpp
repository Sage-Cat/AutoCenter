#include "records.h"
#include "ui_records.h"

Records::Records(QWidget *parent, NetworkCommunication *networkCommunication, int ID_List) :
    QWidget(parent),
    ui(new Ui::Records),
    networkCommunication(networkCommunication),
    ID_List(ID_List)
{
    ui->setupUi(this);

    // set information about current customer, seller and datetime
    init_graphical_widgets();
}

Records::~Records()
{
    delete ui;
}

void Records::on_comboBox_Customer_currentIndexChanged(int index)
{
    // edit:[table_name]:[condition]:[data1:data2:...]

    // UPDATE Lists SET ID_Customer=index  WHERE ID=ID_List
    QStringList requestList = {
        SERVER_API[ServerAPI::records_edit],
        DATABASE_TABLES[Tables::lists],
        "ID=" + QString::number(ID_List),
        "ID_Customer=" + QString::number(index)
    };
}

void Records::on_comboBox_Seller_currentIndexChanged(int index)
{
    // UPDATE Lists SET ID_Seller=index  WHERE ID=ID_List
    QStringList requestList = {
        SERVER_API[ServerAPI::records_edit],
        DATABASE_TABLES[Tables::lists],
        "ID=" + QString::number(ID_List),
        "ID_Seller=" + QString::number(index)
    };
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
    ui->comboBox_Seller->addItems(getAllSellersNames());
    ui->comboBox_Seller->setCurrentIndex(record.at(TABLE_LISTS_SELLER_INDEX).toInt());

    ui->comboBox_Customer->addItems(getAllCustomersNames());
    ui->comboBox_Customer->setCurrentIndex(record.at(TABLE_LISTS_CUSTOMER_INDEX).toInt());

    // set tableWidget & set line_sum
    on_btn_refresh_clicked();
}

void Records::update_line_sum()
{
    double sum = 0.0;
    for(int row = 0; row < ui->tableWidget->rowCount(); ++row)
        sum += ui->tableWidget->item(row, VIEW_RECORDS_PRICE_INDEX)->data(Qt::DisplayRole).toDouble();

    ui->line_sum->setText(QString::number(sum, 'f', 2));
}

QStringList Records::getAllCustomersNames()
{
    // SELECT * FROM Customers WHERE TRUE
    QStringList requestList = {
        SERVER_API[ServerAPI::records_get],
        DATABASE_TABLES[Tables::customers],
        "TRUE"
    };
    emit networkCommunication->requestReady(requestList.join(DELIMITERS[delims::primary]));

    QStringList listOf_Customers_Names;
    for(const auto &record : networkCommunication->getResponseWhenReady().split(DELIMITERS[delims::primary]))
        listOf_Customers_Names << record.split(DELIMITERS[delims::secondary]).at(0);

    return listOf_Customers_Names;
}

QStringList Records::getAllSellersNames()
{
    // SELECT * FROM Customers WHERE TRUE
    QStringList requestList = {
        SERVER_API[ServerAPI::records_get],
        DATABASE_TABLES[Tables::sellers],
        "TRUE"
    };
    emit networkCommunication->requestReady(requestList.join(DELIMITERS[delims::primary]));

    QStringList listOf_Sellers_Names;
    for(const auto &record : networkCommunication->getResponseWhenReady().split(DELIMITERS[delims::primary]))
        listOf_Sellers_Names << record.split(DELIMITERS[delims::secondary]).at(0);

    return listOf_Sellers_Names;
}


void Records::on_btn_refresh_clicked()
{
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
            ui->tableWidget->setItem(row, col, new QTableWidgetItem(recordsList[row][col]));

    ui->tableWidget->setHorizontalHeaderLabels(RECORDS_COLUMNS_NAMES);

    // hide id column
    ui->tableWidget->setColumnHidden(VIEW_RECORDS_ID_LIST_INDEX, true);

    // update line_sum
    update_line_sum();
}

