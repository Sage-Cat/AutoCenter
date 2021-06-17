#include "records.h"
#include "ui_records.h"

#include <QString>

#include <QPrinter>
#include <QPrintDialog>
#include <QFile>

#include <QDesktopServices>
#include <QUrl>

#include "qdialogs/print_document.h"
#include "qdialogs/print_barcode.h"

Records::Records(QWidget *parent, TcpClient *client) :
    QWidget(parent),
    ui(new Ui::Records),
    client(client)
{
    ui->setupUi(this);

    RecordsList recordsList = {
        {
            "1496886698",	"1012080",	"4011100090",	"Шина 225/55R17 97W Ventus S1 evo2 K117 (Hankook)",	"4", "шт.",	"2488,44"
        },

        {
            "46103100",	"302.350",	"8484900090",	"Комплект прокладок",  "1",	"компл",	"612,12"
        },

        {
            "6900273294",	"F 000 ZS0 001",	"8511300098",	"Котушка запалювання (вир-во Bosch)", "1",	"шт.",	"1552,80"
        }
    };


    ui->tableWidget->setRowCount(3);
    ui->tableWidget->setColumnCount(RECORDS_COLUMNS_NAMES.size());
    for(int i = 0; i < int(recordsList.size()); i++)
        for(int j = 0; j < recordsList.at(0).size(); j++)
            ui->tableWidget->setItem(i, j, new QTableWidgetItem(recordsList[i][j]));

    ui->tableWidget->setColumnWidth(3, 600);
    ui->tableWidget->setHorizontalHeaderLabels(RECORDS_COLUMNS_NAMES);

    ui->line_sum->setText(QString::number(2488.44 * 4 + 612.12 + 1552.80));

}

Records::~Records()
{
    delete ui;
}

void Records::on_btn_add_clicked()
{

}

void Records::on_btn_del_clicked()
{

}

void Records::on_btn_refresh_clicked()
{

}

void Records::on_btn_print_document_clicked()
{
    Print_document * dlg = new Print_document;
    if(dlg->exec() == QDialog::Accepted)
    {
        QDesktopServices::openUrl(QUrl("file:///" + QCoreApplication::applicationDirPath() + "/pdv_rahunok000.htm"));
    }
}

void Records::on_btn_print_barcode_clicked()
{
    Print_barcode * dlg = new Print_barcode;
    if(dlg->exec() == QDialog::Accepted)
    {
        QDesktopServices::openUrl(QUrl("file:///" + QCoreApplication::applicationDirPath() + "/label000.htm"));
    }
}
