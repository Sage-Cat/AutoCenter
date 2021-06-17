#include "lists.h"
#include "ui_lists.h"

Lists::Lists(QWidget *parent, TcpClient *client) :
    QWidget(parent),
    ui(new Ui::Lists),
    client(client)
{
    ui->setupUi(this);

    ui->tableWidget->setHorizontalHeaderLabels(LISTS_COLUMNS_NAMES);
}

Lists::~Lists()
{
    delete ui;
}

void Lists::on_btn_add_clicked()
{

}

void Lists::on_btn_del_clicked()
{

}

void Lists::on_btn_refresh_clicked()
{

}

void Lists::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{
    emit openRecords();
}
