#ifndef INVENTORY_H
#define INVENTORY_H

#include <QWidget>

#include <tcpclient.h>

namespace Ui {
class Inventory;
}

class Inventory : public QWidget
{
    Q_OBJECT

public:
    explicit Inventory(QWidget *parent = nullptr, TcpClient *client = new TcpClient());
    ~Inventory();

private slots:
    void on_btn_del_clicked();

    void on_btn_refresh_clicked();

    void on_btn_check_clicked();

private:
    Ui::Inventory *ui;
    TcpClient *client;
    RecordsList recordsList;
};

#endif // INVENTORY_H
