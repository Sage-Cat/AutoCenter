#ifndef NETWORKCOMMUNICATION_H
#define NETWORKCOMMUNICATION_H

#include <QObject>

class NetworkCommunication
{
public:
    NetworkCommunication();

    QString getResponse() const;

signals:
    void requestCreated(QString request);

public slots:
    virtual void setResponse(QString response);

private:
    QString response;
};

#endif // NETWORKCOMMUNICATION_H
