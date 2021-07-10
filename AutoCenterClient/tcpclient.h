#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QSemaphore>

#include "statements.h"

class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = nullptr, QHostAddress hostname = QHostAddress::LocalHost, int port = DEFAULT_PORT);
    bool isAdmin();

    void setUID(const QString &value);
    void setAdmin(bool value);

    static QSemaphore s_semaphore;
    static QString s_response;

public slots:
    void sendAndGetResponse(const QString &request);

signals:
    void errorDetected(QString);

private /* methods */:
    bool connect();
    void disconect();

private:
    QTcpSocket *socket;
    QString UID;
    bool admin;

    QHostAddress currentHostname;
    int currentPort;
};

#endif // TCPCLIENT_H
