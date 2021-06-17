#ifndef LOAD_SUPPLIER_INVOICE_H
#define LOAD_SUPPLIER_INVOICE_H

#include <QDialog>

#include <tcpclient.h>

namespace Ui {
class Load_supplier_invoice;
}

class Load_supplier_invoice : public QDialog
{
    Q_OBJECT

public:
    explicit Load_supplier_invoice(QWidget *parent = nullptr, TcpClient *client = new TcpClient());
    ~Load_supplier_invoice();

private slots:
    void on_btn_explorer_clicked();

    void on_btn_load_clicked();

private:
    Ui::Load_supplier_invoice *ui;
    TcpClient *client;
};

#endif // LOAD_SUPPLIER_INVOICE_H
