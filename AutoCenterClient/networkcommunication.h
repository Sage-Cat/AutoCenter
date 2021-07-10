#ifndef NETWORKCOMMUNICATION_H
#define NETWORKCOMMUNICATION_H

#include <QObject>
#include "tcpclient.h"

class NetworkCommunication : public QObject
{
    Q_OBJECT

public:
    NetworkCommunication(TcpClient *tcpClient);

    QString getResponseWhenReady();

signals:
    void requestReady(QString request);

public slots:
    void handleCriticalError(QString message);
};

#endif // NETWORKCOMMUNICATION_H
