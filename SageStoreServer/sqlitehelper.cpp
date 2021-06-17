#include "sqlitehelper.h"

#include <QFile>
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <QDataStream>

SQLiteHelper::SQLiteHelper(QObject *parent, QString db_name) :
    QObject(parent),
    request(""),
    response("")
{
    /* DB INIT */
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(db_name);
    qDebug() << "Opening the DB... " << db.open();

    QFile file(":/sql/db_init.sql");
    qDebug() << "Finding db_init.sql script... " << file.open(QIODevice::ReadOnly);

    // Parsing the db_init.sql file and executing queries
    qry = new QSqlQuery(db);
    auto list = QString(file.readAll()).split('|');
    while(list.size() != 0)
    {
        // 0 - Information
        // 1 - Query
        QString qryName = list.at(0);
        bool result = qry->exec(list.at(1));
        if(result)
            qDebug() << "Processing:" << qryName << "... " << result;
        else
            qDebug() << "Processing:" << qryName << "... " << qry->lastError().text();

        list.pop_front();
        list.pop_front();
    }

}
