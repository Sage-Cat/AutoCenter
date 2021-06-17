#ifndef RECORDS_H
#define RECORDS_H

#include <QWidget>

#include <tcpclient.h>

namespace Ui {
class Records;
}

class Records : public QWidget
{
    Q_OBJECT

public:
    explicit Records(QWidget *parent = nullptr, TcpClient *client = new TcpClient());
    ~Records();

private slots:
    void on_btn_add_clicked();
    void on_btn_del_clicked();
    void on_btn_refresh_clicked();
    void on_btn_print_document_clicked();
    void on_btn_print_barcode_clicked();

private:
    Ui::Records *ui;
    TcpClient *client;
};

#endif // RECORDS_H
