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
    qDebug() << "Request: " << request;

    params = new QStringList(request.split(DELIMITERS[0]));
    if(params->at(0) != "client")
        return; // ignore incorrect request
    params->pop_front();

    // UID
    UID = params->at(0);
    params->pop_front();

    // Command
    QString cmd = params->at(0);
    params->pop_front();

    // Information
    QString response = "server" + DELIMITERS[0],
            log_msg = "";

    /* DECODE */

    /* --------------- ADD --------------- */
    // add:[table_name]:[data1:data2:...] - data example: " Name_Seller='John' "
    if(cmd == "add")
    {
        QString table_name = params->at(0);
        params->pop_front();

        response += dbHelper->add(table_name, params);
    }
    /* --------------- DEL --------------- */
    // del:[table_name]:[condition] - condition example: " ID_List=1 "
    else if(cmd == "del")
    {
        response += dbHelper->del(params->at(0), params->at(1));
    }
    /* --------------- EDIT --------------- */
    // edit:[table_name]:[condition]:[data1:data2:...]
    else if(cmd == "edit")
    {
        QString table_name = params->at(0);
        params->pop_front();
        QString condition = params->at(0);
        params->pop_front();

        response += dbHelper->edit(table_name, condition, params);
    }
    /* --------------- GET --------------- */
    // get:[table_name or view_name]:[condition]
    else if(cmd == "get")
    {
        response += dbHelper->get(params->at(0), params->at(1));
    }

    /* SEND RESPONSE TO THE CLIENT */
    socket->write(response.toUtf8());
    qDebug() << "Response: " << response;
    socket->flush();
    qDebug() << "************************";

    /* LOG ACTIVITY */
//    if(log_msg != "")
//        dbHelper->log_activity(UID, log_msg);

    delete params;
    params = nullptr;
}
