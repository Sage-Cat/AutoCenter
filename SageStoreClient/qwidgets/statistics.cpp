#include "statistics.h"
#include "ui_statistics.h"

Statistics::Statistics(QWidget *parent, TcpClient *client) :
    QWidget(parent),
    ui(new Ui::Statistics),
    client(client)
{
    ui->setupUi(this);
}

Statistics::~Statistics()
{
    delete ui;
}
