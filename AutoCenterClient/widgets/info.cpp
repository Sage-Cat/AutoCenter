#include "info.h"
#include "ui_info.h"

Info::Info(QWidget *parent, NetworkCommunication *networkCommunication, Tables table, int ID) :
    QWidget(parent),
    ui(new Ui::Info),
    networkCommunication(networkCommunication),
    table(table),
    ID(ID)
{
    ui->setupUi(this);

    // SELECT * FROM table WHERE ID=ID
    QStringList requestList = {
        SERVER_API[Api::_get],
        DATABASE_TABLES[table],
        "ID=" + QString::number(ID)
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

    // hide ID (last column)
    ui->tableWidget->setColumnHidden(column_count - 1, true);

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

Info::~Info()
{
    delete ui;
}
