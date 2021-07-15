#ifndef INFO_H
#define INFO_H

#include <QWidget>

#include "networkcommunication.h"

namespace Ui {
class Info;
}

class Info : public QWidget
{
    Q_OBJECT

public:
    explicit Info(QWidget *parent = nullptr,
                  NetworkCommunication *networkCommunication = new NetworkCommunication(new TcpClient),
                  Tables table = Tables::info_customer,
                  int ID = 0);
    ~Info();

private:
    Ui::Info *ui;
    NetworkCommunication *networkCommunication;
    Tables table;
    int ID;
};

#endif // INFO_H
