#include "print_document.h"
#include "ui_print_document.h"

#include <QPrinter>
#include <QFile>
#include <QPrintDialog>
#include <QTextDocument>

Print_document::Print_document(QWidget *parent, TcpClient *client) :
    QDialog(parent),
    ui(new Ui::Print_document),
    client(client)
{
    ui->setupUi(this);
}

Print_document::~Print_document()
{
    delete ui;
}

void Print_document::on_btn_print_clicked()
{
    accept();
}

void Print_document::on_comboBox_currentIndexChanged(int index)
{
}
