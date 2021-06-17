#ifndef LISTS_H
#define LISTS_H

#include <QWidget>
#include <QTableWidgetItem>

#include <tcpclient.h>

namespace Ui {
class Lists;
}

class Lists : public QWidget
{
    Q_OBJECT

public:
    explicit Lists(QWidget *parent = nullptr, TcpClient *client = new TcpClient());
    ~Lists();

private slots:
    void on_btn_add_clicked();

    void on_btn_del_clicked();

    void on_btn_refresh_clicked();

    void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);

signals:
    void openRecords();

private:
    Ui::Lists *ui;
    TcpClient *client;
};

#endif // LISTS_H
