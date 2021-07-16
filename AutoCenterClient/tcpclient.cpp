#include "tcpclient.h"

QSemaphore TcpClient::s_semaphore;
QString TcpClient::s_response;

TcpClient::TcpClient(QObject *parent, QHostAddress hostname, int port) :
    QObject(parent),
    UID("-1"),
    currentHostname(hostname),
    currentPort(port)
{
}

bool TcpClient::connect()
{
    socket = new QTcpSocket;
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
    delete socket;
}

bool TcpClient::isAdmin()
{
    return admin;
}

void TcpClient::sendAndGetResponse(const QString &request)
{
    QString response = "";
    if(connect())
    {
        /* SENDING */
        QByteArray msg = ("client" + DELIMITERS[Delimiters::primary] + UID + DELIMITERS[Delimiters::primary] + request).toUtf8();
        socket->write(msg);
        socket->waitForBytesWritten(2000);

        /* GETTING THE RESPONSE */
        socket->waitForReadyRead(5000);

        while(response.mid(0, QString("server" + DELIMITERS[Delimiters::primary]).length())
              != "server" + DELIMITERS[Delimiters::primary]) // skip packages from unknown source
        {
            if(socket->bytesAvailable())
                response += QString(socket->readAll());
            else
            {
                emit errorDetected("Сервер довго не відповідає");
                return;
            }
        }

        /* SETTING THE RESPONSE */
        response.remove(0, QString("server" + DELIMITERS[Delimiters::primary]).length());

        s_response = response;
        s_semaphore.release();

        disconect();
    }
}

void TcpClient::setUID(const QString &value)
{
    UID = value;
}

void TcpClient::setAdmin(bool value)
{
    admin = value;
}










