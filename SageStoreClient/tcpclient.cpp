#include "tcpclient.h"

#include <QHostAddress>

TcpClient::TcpClient(QObject *parent) :
    QObject(parent),
    socket(new QTcpSocket),
    UID("-1")
{
}

bool TcpClient::connect(QHostAddress hostname, int port)
{
    socket->connectToHost(hostname, port);

    if(!socket->waitForConnected(3000))
    {
        emit errorDetected("Не можу підключитися до сервера");
        return false;
    }
    return true;
}

void TcpClient::disconect()
{
    socket->close();
}

bool TcpClient::isAdmin()
{
    return admin;
}

QString TcpClient::send_and_get_response(const QString &request)
{
    QString response = "";
    if(connect(QHostAddress::LocalHost, 9999))
    {
        QByteArray msg = ("client" + DELIMITER_MAIN + UID + DELIMITER_MAIN + request).toUtf8();
        socket->write(msg);
        socket->waitForBytesWritten(2000);
        socket->waitForReadyRead(5000);

        if(socket->bytesAvailable())
            response += QString(socket->readAll());
        else
            emit errorDetected("Сервер довго не відповідає");

        if(response.mid(0, QString("server" + DELIMITER_MAIN).length()) != "server" + DELIMITER_MAIN)
            emit errorDetected("Отримано повідомлення від невідомого відправника");
        else
            response.remove(0, QString("server" + DELIMITER_MAIN).length());

        disconect();
    }

    return response;
}

void TcpClient::setUID(const QString &value)
{
    UID = value;
}

void TcpClient::setAdmin(bool value)
{
    admin = value;
}

void TcpClient::sendData(const QString &request)
{
    send_and_get_response(request);
}











