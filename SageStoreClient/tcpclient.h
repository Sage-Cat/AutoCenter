#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>

#include "statements.h"

class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = nullptr);

    bool connect(QHostAddress hostname = QHostAddress::LocalHost, int port = DEFAULT_PORT);
    void disconect();
    bool isAdmin();

     QString send_and_get_response(const QString &request);
     void setUID(const QString &value);
     void setAdmin(bool value);

public slots:
    void sendData(const QString &request);

signals:
    void errorDetected(QString message);

private:
    QTcpSocket *socket;
    QString UID;
    bool admin;
};

#endif // TCPCLIENT_H
