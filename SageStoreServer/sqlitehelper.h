#ifndef SQLITEHELPER_H
#define SQLITEHELPER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "statements.h"

class SQLiteHelper : public QObject
{
    Q_OBJECT
public:
    explicit SQLiteHelper(QObject *parent = nullptr, QString db_name = DEFAULT_DB_NAME);

    QString getLastRequest() const;
    QString getLastResponse() const;

    /* according server_API */


private:
    QSqlDatabase db;
    QSqlQuery *qry;
    QString request, response;
};

#endif // SQLITEHELPER_H
