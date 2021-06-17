#ifndef STATISTICS_H
#define STATISTICS_H

#include <QWidget>

#include <tcpclient.h>

namespace Ui {
class Statistics;
}

class Statistics : public QWidget
{
    Q_OBJECT

public:
    explicit Statistics(QWidget *parent = nullptr, TcpClient *client = new TcpClient());
    ~Statistics();

private:
    Ui::Statistics *ui;
    TcpClient *client;
};

#endif // STATISTICS_H
