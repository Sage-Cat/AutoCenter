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

QString SQLiteHelper::add(QString table_name, QStringList *data)
{
    // INSERT INTO table(COLUMN_NAME, ...) VALUES('John', ...);
    request = "INSERT INTO " + table_name + " VALUES(" + data->join(", ") + ");";
    if(!qry->exec(request))
        return "-1";
    else
    {
        table_name = table_name.mid(0, table_name.indexOf('(')); // table_name without column names

        request = "SELECT IFNULL(MAX(ID), -1) FROM " + table_name;
        if(!qry->exec(request))
            return "-1";
        else
        {
            qry->next();
            return qry->value(0).toString();
        }
    }
}

QString SQLiteHelper::del(QString table_name, QString condition)
{
    // DELETE (everything is fine cuz foreign key set "ON DELETE CASCADE")
    request = "DELETE FROM " + table_name + " WHERE " + condition;

    return QString::number(qry->exec(request)); // maybe always true
}

QString SQLiteHelper::edit(QString table_name, QString condition, QStringList *data)
{
    request = "UPDATE " + table_name + " SET " + data->join(", ") + " WHERE " + condition;

    return QString::number(qry->exec(request));
}

QString SQLiteHelper::get(QString table_name, QString condition)
{
    request = "SELECT * FROM " + table_name + " WHERE " + condition;

    response = "";
    if(qry->exec(request))
    {
        // if query is fine
        while(qry->next())
        {
            for(int i = 0; i < qry->record().count(); ++i)
               response += qry->value(i).toString() + DELIMITERS[delims::secondary];

            // replacing the last rows delimiter with primary delimiter, due to the end of the row
            response.remove(response.length() - DELIMITERS[delims::secondary].length(), DELIMITERS[delims::secondary].length());
            response += DELIMITERS[delims::primary];
        }
        return response.mid(0, response.length() - DELIMITERS[delims::primary].length()); // return without the last DELIMITERS[delims::primary]
    }
    else
    {
        qDebug() << "get error:" << qry->lastError().text();
        return "-1"; // return error
    }
}
