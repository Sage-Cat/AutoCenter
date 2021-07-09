#include "changelisttype.h"
#include "ui_changelisttype.h"

ChangeListType::ChangeListType(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeListType)
{
    ui->setupUi(this);

    ui->comboBox->addItems(LISTTYPE_NAMES);
}

ChangeListType::~ChangeListType()
{
    delete ui;
}

void ChangeListType::on_btn_change_clicked()
{
    emit typeSelected(ui->comboBox->currentIndex());

    this->accept();
}

