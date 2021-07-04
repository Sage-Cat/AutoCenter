#ifndef NETWORKCOMMUNICATION_H
#define NETWORKCOMMUNICATION_H

#include <QObject>
#include "tcpclient.h"

class NetworkCommunication : public QObject
{
    Q_OBJECT

public:
    NetworkCommunication(const TcpClient *tcpClient);

    QString getResponse() const;

signals:
    void requestReady(QString request);

public slots:
    void setResponse(QString response);
    void handleCriticalError(QString message);

private:
    QString response;
};

#endif // NETWORKCOMMUNICATION_H
