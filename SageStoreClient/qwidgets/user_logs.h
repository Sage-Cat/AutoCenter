#ifndef USER_LOGS_H
#define USER_LOGS_H

#include <QWidget>

#include <tcpclient.h>

namespace Ui {
class User_logs;
}

class User_logs : public QWidget
{
    Q_OBJECT

public:
    explicit User_logs(QWidget *parent = nullptr, TcpClient *client = new TcpClient());
    ~User_logs();

private slots:

    void on_dateTime_from_dateTimeChanged(const QDateTime &dateTime);

    void on_dateTime_to_dateTimeChanged(const QDateTime &dateTime);

private:
    Ui::User_logs *ui;
    TcpClient *client;
};

#endif // USER_LOGS_H
