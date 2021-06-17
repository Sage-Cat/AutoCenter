#ifndef SELLERS_H
#define SELLERS_H

#include <QWidget>
#include <QTableWidgetItem>

#include <tcpclient.h>

namespace Ui {
class Sellers;
}

class Sellers : public QWidget
{
    Q_OBJECT

public:
    explicit Sellers(QWidget *parent = nullptr, TcpClient *client = new TcpClient());
    ~Sellers();

private slots:
    void on_btn_add_clicked();
    void on_btn_del_clicked();
    void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);
    void on_btn_refresh_clicked();

private:
    Ui::Sellers *ui;
    TcpClient *client;
    RecordsList recordsList;
};

#endif // SELLERS_H
