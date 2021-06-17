#ifndef PRINT_BARCODE_H
#define PRINT_BARCODE_H

#include <QDialog>

namespace Ui {
class Print_barcode;
}

class Print_barcode : public QDialog
{
    Q_OBJECT

public:
    explicit Print_barcode(QWidget *parent = nullptr);
    ~Print_barcode();

private:
    Ui::Print_barcode *ui;
};

#endif // PRINT_BARCODE_H
