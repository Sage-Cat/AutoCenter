#ifndef STATEMENTS_H
#define STATEMENTS_H

#include <QString>
#include <QVector>
#include <QStringList>

//! List[N][M], where
//! N - number of rows,
//! M - number of columns
typedef std::vector<QStringList> RecordsList;

const QString DEFAULT_DB_NAME = "database.sl3";

const int MAX_NUMBER_OF_MISSES = 10;
const QStringList DELIMITERS{":::", "|||"};

#endif // STATEMENTS_H
