#include "print_barcode.h"
#include "ui_print_barcode.h"

#include <QValidator>

Print_barcode::Print_barcode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Print_barcode)
{
    ui->setupUi(this);

    // 

    ui->line_count->setValidator(new QIntValidator());

    // ----------------------
}

Print_barcode::~Print_barcode()
{
    delete ui;
}
