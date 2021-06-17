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

void SQLiteHelper::log_activity(QString UID, QString msg)
{
    request = "INSERT INTO UserLogs "
              "VALUES(NULL, ':msg', :UID)";
    request.replace(":msg", msg);
    request.replace(":UID", UID);

    if(!qry->exec(request))
        qDebug() << "log_activity error:" << qry->lastError().text();
}

QString SQLiteHelper::login(QString number, QString password)
{
    request = "SELECT ID_User, isAdmin "
              "FROM Users "
              "WHERE Number=':number' AND Password=':password'";
    request.replace(":number", number);
    request.replace(":password", password);

    if(!qry->exec(request))
        qDebug() << "login error:" << qry->lastError().text();
    else
    {
        qry->next();
        QString UID = qry->value(0).toString(),
                isAdmin = qry->value(1).toString();

        return UID +DELIMITER_MAIN+ isAdmin;
    }
    return "-1"; // error
}

bool SQLiteHelper::add(QString table, QStringList *params)
{
    // INSERT INTO table VALUES('value1', ... , NULL)
    request = "INSERT INTO " + table + " VALUES('" + params->join("', '") + "', NULL);";

    return qry->exec(request);
}

bool SQLiteHelper::del(QString table, QString filter)
{
    // FIRSTLY, we need to clear all references from the foreing keys
    request = "";
    if(table == "Lists")
        request += "DELETE FROM Records WHERE " + filter;
    else if(table == "Users")
        request += "DELETE FROM UserLogs WHERE " + filter;

    if(request != "")
        qry->exec(request);

    // DELETE
    request = "DELETE FROM :table WHERE :filter;";
    request.replace(":table", table);
    request.replace(":filter", filter);

    return qry->exec(request); // maybe always true
}

bool SQLiteHelper::edit(QString table, QStringList *params, QString filter)
{
    request = "UPDATE " + table + " SET " + params->join(", ") + "WHERE " + filter;

    return qry->exec(request);
}

QString SQLiteHelper::get(QString table, QString filter)
{  
    request = "SELECT * FROM :table "
              "WHERE :filter";
    request.replace(":table", table);
    request.replace(":filter", filter);

    response = "";
    if(!qry->exec(request))
        qDebug() << "get error:" << qry->lastError().text();
    else
    {
        while(qry->next())
        {
            for(int i = 0; i < qry->record().count(); ++i)
               response += qry->value(i).toString() + DELIMITER_AUXILIARY;

            // replacing the last DELIMITER_AUXILIARY with DELIMITER_MAIN, due to the end of the record
            response.remove(response.length() - DELIMITER_AUXILIARY.length(), DELIMITER_AUXILIARY.length());
            response += DELIMITER_MAIN;
        }
        return response.mid(0, response.length() - DELIMITER_MAIN.length()); // return without the last DELIMITER_MAIN
    }
    return "-1";
}

bool SQLiteHelper::addProductTypes(RecordsList *recordsList)
{
    for(size_t n = 0; n < recordsList->size(); ++n)
    {
        // VALUES: Amount, ID, ...
        request = "INSERT INTO ProductTypes "
                  "VALUES(0, NULL, '" + recordsList->at(n).join("', '") + "')";
        if(!qry->exec(request))
            return false;
    }
    return true;
}

QString SQLiteHelper::statistics(QString from, QString to)
// SQLite datetime format 'YYYY-MM-DD HH:MM:SS'
{
    response = "";

    // 1. GET THE "GROSS INCOME"
    request = "SELECT SUM(Price) "
              "FROM Statistics "
              "WHERE DateTime>':from' AND DateTime < ':to'";
    request.replace(":from", from);
    request.replace(":to", to);

    if(!qry->exec(request))
        qDebug() << "statistics error:" << qry->lastError().text();
    qry->next();
    response += qry->value(0).toString();

    // 2. GET THE "TOP 10 CUSTOMERS"
    request =
           "SELECT Name_Customer, SUM(Price) AS SUM \
            FROM Statistics \
            WHERE DateTime>':from' AND DateTime < ':to' \
            GROUP BY Name_Customer \
            ORDER BY SUM DESC \
            LIMIT 10";

    if(!qry->exec(request))
        qDebug() << "statistics error:" << qry->lastError().text();
    while(qry->next())
        response +=DELIMITER_MAIN+ qry->value(0).toString() + "|" + qry->value(1).toString();

    return response;
}

bool SQLiteHelper::setList(QStringList *params)
// params: [ID_List]:[ID_Seller]:[ID_Customer]:[new Records /DELIMITER_MAIN= "|"]
{
    // ID_List
    QString ID_List = params->at(0);
    params->pop_front();

    // ID_Seller
    QString ID_Seller = params->at(0);
    params->pop_front();

    // ID_Customer
    QString ID_Customer = params->at(0);
    params->pop_front();

    // IF -1 THEN CREATE EMPTY LIST
    if(params->at(0) == "-1")
    {
        /* #1 get this year MAX(ListNumber)+1 */
        request = "SELECT ifnull(MAX(ListNumber), -1) "
                  "FROM Lists "
                  "WHERE strftime('%Y', Lists.DateTime) = strftime('%Y', DATE('now'))";
        if(!qry->exec(request))
        {
            qDebug() << "setList error #1:" << qry->lastError().text();
            return false;
        }
        // "MAX + 1"
        QString ListNumber = QString::number(qry->value(0).toInt() + 1);


        /* #2 Update ID_List */
        if(!qry->exec("SELECT MAX(ID_List) FROM Lists"))
        {
            qDebug() << "setList error #2:" << qry->lastError().text();
            return false;
        }
        ID_List = qry->value(0).toString(); // OUR ID_List


        /* #3 add new list with default params */
        request = "INSERT INTO Lists(ListNumber, ListType, ID_Seller, ID_Customer) "
                  "VALUES(:ListNumber, '0', 0, 0);";
        request.replace(":ListNumber", ListNumber);
        if(!qry->exec(request))
        {
            qDebug() << "setList error #3:" << qry->lastError().text();
            return false;
        }
    }

    // SETTING THE DATA
    if(params->at(0) != "") // if there are records to put in the list
    {
        /* #4 FIRSTLY, DELETE OLD */
        request = "DELETE FROM Records WHERE ID_List=" + ID_List;
        if(!qry->exec(request))
        {
            qDebug() << "setList error #4:" << qry->lastError().text();
            return false;
        }

        /* #5 INSERT NEW */
        for(int i = 0; i < params->size(); ++i)
            // VALUES: ID_Record, Count, Price, ID_ProductType, ID_List
        {
            auto values = params->at(i).split("|");
            request = "INSERT INTO Records VALUES(NULL, " + values.join(", ") + ")";

            if(!qry->exec(request))
            {
                qDebug() << "setList error #5:" << qry->lastError().text();
                return false;
            }
        }
    }

    return true;
}

QString SQLiteHelper::findProduct(QString code)
{
    request = "SELECT * FROM ProductTypes WHERE Code='" + code +"';";
    if(!qry->exec())
        qDebug() << "get error:" << qry->lastError().text();

    response = "";
    qry->next();
    for(int i = 0; i < qry->record().count(); ++i)
        response += qry->value(i).toString() + "|";

    return response;
}

QString SQLiteHelper::getLastRequest() const
{
    return request;
}

QString SQLiteHelper::getLastResponse() const
{
    return response;
}
