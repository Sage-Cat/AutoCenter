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

//    void log_activity(QString UID, QString message);

    /* according server_API */
    QString add(QString table_name, QStringList *data);
    QString del(QString table_name, QString condition);
    QString edit(QString table_name, QString condition, QStringList *data);
    QString get(QString table_name, QString condition);
//    QString login(QString number, QString password);
//    QString statistics(QString datetime_from, QString datetime_to);
//    QString pricelist(RecordsList *recordsList);

private:
    QSqlDatabase db;
    QSqlQuery *qry;
    QString request, response;
};

#endif // SQLITEHELPER_H
