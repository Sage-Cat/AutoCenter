#ifndef STATEMENTS_H
#define STATEMENTS_H

#include <QString>
#include <QVector>
#include <QStringList>
#include <QMap>

//! List[N][M], where
//! N - number of rows,
//! M - number of columns
typedef std::vector<QStringList> RecordsList;

const QString DEFAULT_DB_NAME = "database.sl3";

const int MAX_NUMBER_OF_MISSES = 10;

//! Consists of delimiters for transfering data (decode messages using it in direct 0,1... order)
const QStringList DELIMITERS{":::", "|||"};
enum delims {
    primary = 0,
    secondary
};

#endif // STATEMENTS_H
