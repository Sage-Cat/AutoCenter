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

    void log_activity(QString UID, QString msg);

    //! Returns "-1" if error
    QString login(QString number, QString password);
    bool add(QString table, QStringList* params);
    bool del(QString table, QString filter);
    bool edit(QString table, QStringList* params, QString filter);
    QString get(QString table, QString filter);
    bool addProductTypes(RecordsList* recordsList);
    QString statistics(QString from, QString to);
    bool setList(QStringList* params);
    QString findProduct(QString code);

    QString getLastRequest() const;
    QString getLastResponse() const;

private:
    QSqlDatabase db;
    QSqlQuery *qry;
    QString request, response;
};

#endif // SQLITEHELPER_H
