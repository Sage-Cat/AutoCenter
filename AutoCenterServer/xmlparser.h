#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QObject>
#include "statements.h"

class XmlParser : public QObject
{
    Q_OBJECT
public:
    explicit XmlParser(QObject *parent = nullptr);

    RecordsList* parseOmegaPriceList(const QString &xmlData);

private:
    RecordsList recordsList;
    QString lost_part;
};

#endif // XMLPARSER_H
