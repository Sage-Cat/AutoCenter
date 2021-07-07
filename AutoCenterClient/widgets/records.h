#ifndef RECORDS_H
#define RECORDS_H

#include <QWidget>

#include "networkcommunication.h"

namespace Ui {
class Records;
}

class Records : public QWidget
{
    Q_OBJECT

public:
    explicit Records(QWidget *parent = nullptr,
                     NetworkCommunication *networkCommunication = new NetworkCommunication(new TcpClient),
                     int ID_List = 0
              );
    ~Records();

private slots:
    void on_comboBox_Customer_currentIndexChanged(int index);
    void on_comboBox_Seller_currentIndexChanged(int index);

    void on_btn_refresh_clicked();

private /* methods */:
    void init_graphical_widgets();
    void update_line_sum();

    QStringList getAllCustomersNames();
    QStringList getAllSellersNames();

private:
    Ui::Records *ui;
    NetworkCommunication *networkCommunication;
    int ID_List;
};

#endif // RECORDS_H
