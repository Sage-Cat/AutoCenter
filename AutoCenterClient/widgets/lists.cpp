#include "lists.h"
#include "ui_lists.h"

Lists::Lists(BaseWidget *parent, OperationType type) :
    BaseWidget(parent),
    ui(new Ui::Lists),
    type(type)
{
    ui->setupUi(this);
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

void Lists::on_radio_all_clicked()
{

}

void Lists::on_radio_org_clicked()
{

}

void Lists::on_radio_not_org_clicked()
{

}
