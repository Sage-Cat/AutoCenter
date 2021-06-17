#include "mainserver.h"

#include "statements.h"

MainServer::MainServer(QObject *parent) : QObject(parent)
{
    // INIT
    dbHelper = new SQLiteHelper(this);
    xmlParser = new XmlParser(this);
    server = new QTcpServer(this);

    // CONNECT
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    // DO
    if(!server->listen(QHostAddress::Any, 9999))
    {
        qDebug() << "Server could not start";
    }
    else
    {
        qDebug() << "------------------ Server started! ----------------";
        qDebug() << "Address: " << server->serverAddress().toString();
        qDebug() << "Port: " << server->serverPort();
        qDebug() << "---------------------------------------------------";
    }
}

void MainServer::newConnection()
{
    socket = server->nextPendingConnection();

    socket->waitForReadyRead();
    auto request = socket->readAll();
    QString str = QString::fromStdString(request.toStdString());
    this->decode(str);

    socket->close();
}

void MainServer::decode(QString request)
{
//    // qDebug() << "Request: " << request;

//    params = new QStringList(request.split(DELIMITER_MAIN));
//    if(params->at(0) != "client")
//    {
//        qDebug() << "Received a message from an unknown sender.";
//        return;
//    }
//    params->pop_front();

//    // UID
//    UID = params->at(0);
//    params->pop_front();

//    // Command
//    QString cmd = params->at(0);
//    params->pop_front();

//    // Information
//    QString response = "server" + DELIMITER_MAIN,
//            log_msg = "";


    /* DECODE */



//    /* SEND RESPONSE TO THE CLIENT */
//    socket->write(response.toUtf8());
//    qDebug() << "Response: " << response;
//    socket->flush();
//    qDebug() << "************************";

//    /* LOG ACTIVITY */
//    if(log_msg != "")
//        dbHelper->log_activity(UID, log_msg);

//    delete params;
//    params = nullptr;
}
