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
    // qDebug() << "Request: " << request;

    params = new QStringList(request.split(DELIMITER_MAIN));
    if(params->at(0) != "client")
    {
        qDebug() << "Received a message from an unknown sender.";
        return;
    }
    params->pop_front();

    // UID
    UID = params->at(0);
    params->pop_front();

    // Command
    QString cmd = params->at(0);
    params->pop_front();

    // Information
    QString response = "server" + DELIMITER_MAIN,
            log_msg = "";

    /* --------------- ADD --------------- */
    if(cmd == "add")
    {
        QString table = params->at(0);
        params->pop_front();

        bool result = dbHelper->add(table, params);
        response += QString::number(result);

        if(result)
            log_msg += "Додано новий запис у " + table + " для " + params->at(0);
    }
    /* --------------- DEL --------------- */
    else if(cmd == "del")
    {
        // params: table and filter
        bool result = dbHelper->del(params->at(0), params->at(1));
        response += QString::number(result);

        if(result)
            log_msg += "Видалено з " + params->at(0) + " запис де " + params->at(1);
    }
    /* --------------- EDIT --------------- */
    else if(cmd == "edit")
    {
        QString table = params->at(0);
        params->pop_front();
        QString filter = params->at(0);
        params->pop_front();

        response += QString::number(dbHelper->edit(table, params, filter));

        if(response != "Server:")
            log_msg += "Редаговано запис у " + table + " де " + filter;
    }
    /* --------------- GET --------------- */
    else if(cmd == "get")
    {
        // params: table and filter
        response += dbHelper->get(params->at(0), params->at(1));
    }
    /* --------------- LOGIN --------------- */
    else if(cmd == "login")
    {
        // params: number and password
        response += dbHelper->login(params->at(0), params->at(1));

        if(response != "Server" +DELIMITER_MAIN+ UID +DELIMITER_MAIN+ "-1")
            log_msg += "У систему увійшов користувач " + params->at(0);
    }
    /* --------------- UNIQ --------------- */
    else if(cmd == "uniq")
    {
        QString cmd_uniq = params->at(0);
        params->pop_front();

        // -------------- UNIQ addProductTypes --------------
        if(cmd_uniq == "addProductTypes")
        {
            QString supplier = params->at(0);
            params->pop_front();

            // pointer to xml parsing result
            RecordsList *recordList = nullptr;

            // parse according to supplier
            if(supplier == "Omega")
                recordList = xmlParser->parseOmega(params->at(0));

            // add records to DB
            bool result = dbHelper->addProductTypes(recordList);
            response += QString::number(result);

            if(result)
                log_msg += "Додання нових видів товарів від постачальника " + supplier;
        }
        // -------------- UNIQ statistics --------------
        else if(cmd_uniq == "statistics")
        {
            // params: datetime_from and datetime_to
            response += dbHelper->statistics(params->at(0), params->at(1));
        }
        // -------------- UNIQ updateList --------------
        else if(cmd_uniq == "setList")
        {
            // params: [ID_List]:[ID_Seller]:[ID_Customer]:[new Records /DELIMITER_MAIN= "|"]
            response += QString::number(dbHelper->setList(params));

            if(response != "server:")
                log_msg += "Створ./Редаг. списку №" + params->at(0) +
                        ", продавець №" + params->at(1) +
                        ", покупець №" + params->at(2);
        }
        // -------------- UNIQ findProduct --------------
        else if(cmd_uniq == "findProduct")
        {
            // params: code
            response += dbHelper->findProduct(params->at(0));
        }
    }

    /* SEND RESPONSE TO THE CLIENT */
    socket->write(response.toUtf8());
    qDebug() << "Response: " << response;
    socket->flush();
    qDebug() << "************************";

    /* LOG ACTIVITY */
    if(log_msg != "")
        dbHelper->log_activity(UID, log_msg);

    delete params;
    params = nullptr;
}
