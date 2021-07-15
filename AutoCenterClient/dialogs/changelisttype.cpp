#include "changelisttype.h"
#include "ui_changelisttype.h"

ChangeListType::ChangeListType(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeListType)
{
    ui->setupUi(this);

    QStringList listOfTypes;
    for(const auto &value : LIST_TYPES.values())
        listOfTypes << value;

    ui->comboBox->addItems(listOfTypes);
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

