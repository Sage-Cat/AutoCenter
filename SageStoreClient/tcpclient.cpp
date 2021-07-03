#include "tcpclient.h"

TcpClient::TcpClient(QObject *parent, QHostAddress hostname, int port) :
    QObject(parent),
    socket(new QTcpSocket),
    UID("-1"),
    currentHostname(hostname),
    currentPort(port)
{
}

bool TcpClient::connect()
{
    socket->connectToHost(currentHostname, currentPort);

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

QString TcpClient::sendAndGetResponse(const QString &request)
{
    QString response = "";
    if(connect())
    {
        /* SENDING */
        QByteArray msg = ("client" + DELIMITERS[delims::primary] + UID + DELIMITERS[delims::primary] + request).toUtf8();
        socket->write(msg);
        socket->waitForBytesWritten(2000);

        /* GETING THE RESPONSE */
        socket->waitForReadyRead(5000);

        while(response.mid(0, QString("server" + DELIMITERS[delims::primary]).length())
              != "server" + DELIMITERS[delims::primary]) // skip packages from unknown source
        {
            if(socket->bytesAvailable())
                response += QString(socket->readAll());
            else
            {
                emit errorDetected("Сервер довго не відповідає");
                break;
            }
        }

        // remove standart server prefix
        response.remove(0, QString("server" + DELIMITERS[delims::primary]).length());

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










