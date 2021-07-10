#ifndef MAINSERVER_H
#define MAINSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include "sqlitehelper.h"
#include "xmlparser.h"

class MainServer : public QObject
{
    Q_OBJECT
public:
    explicit MainServer(QObject *parent = nullptr);

public slots:
    void newConnection();

private /* methods */:
    void decode(QString request);

private:
    SQLiteHelper* dbHelper;
    XmlParser* xmlParser;

    QTcpServer* server;
    QTcpSocket* socket;

    QString UID;
    QStringList* params;
};

#endif // MAINSERVER_H
