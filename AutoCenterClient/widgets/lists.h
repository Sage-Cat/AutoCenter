#ifndef LISTS_H
#define LISTS_H

#include <QWidget>

#include "networkcommunication.h"

namespace Ui {
class Lists;
}

class Lists : public QWidget
{
    Q_OBJECT

public:
    explicit Lists(QWidget *parent = nullptr,
                   NetworkCommunication *networkCommunication = new NetworkCommunication(new TcpClient),
                   OperationType type = OperationType::sale
            );
    ~Lists();

signals:
    void tabRecordsRequested(int ID_List, OperationType type);

private slots:
    void on_btn_add_clicked();
    void on_btn_del_clicked();
    void on_btn_refresh_clicked();

    void on_radio_all_clicked();
    void on_radio_org_clicked();
    void on_radio_not_org_clicked();

    void on_tableWidget_cellDoubleClicked(int row, int);

private:
    Ui::Lists *ui;
    NetworkCommunication *networkCommunication;
    OperationType type;
};

#endif // LISTS_H
