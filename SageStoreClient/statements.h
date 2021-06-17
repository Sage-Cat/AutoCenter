#ifndef STATEMENTS_H
#define STATEMENTS_H

#include <QString>
#include <QVector>
#include <QStringList>

//! List[N][M], where
//! N - number of rows,
//! M - number of columns
typedef std::vector<QStringList> RecordsList;

/*! Names of documents from docs/Status_of_documents(ukr).jpg */
enum DocType {
    REC = 0,
    ACC,
    SAL,
    TAX,
    RET
};

// TCP Connection
const QString DEFAULT_HOSTNAME = "google.com";
const int DEFAULT_PORT = 80;
const QString DELIMITER_MAIN = ":::";
const QString DELIMITER_AUXILIARY = "|||";

// Customers & Sellers
const int CUSTOMERS_COLUMNS_COUNT = 9;
const QStringList CUSTOMERS_COLUMNS_NAMES{"Ім'я", "IBAN", "Банк", "ЄДРПОУ", "ІПН", "Адреса", "Телефон", "Ел. пошта", "ID"};
const int SELLERS_COLUMNS_COUNT = 7;
const QStringList SELLERS_COLUMNS_NAMES{"Ім'я", "IBAN", "Банк", "ЄДРПОУ", "ІПН", "Адреса", "ID"};

// Lists & Records
const QStringList LISTS_COLUMNS_NAMES{"Коли", "Номер документа", "Продавець", "Покупець"};
const QStringList RECORDS_COLUMNS_NAMES{"Код", "Каталожний номер", "Код ТНВЕД", "Назва", "Одиниці", "Кількість", "Ціна"};

// Inventory
const QStringList INVENTORY_COLUMNS_NAMES{"Кількість", "", "Код",  "Каталожний номер", "Код ТНВЕД", "Назва", "Одиниці", ""};

// XML pricelist's lines sending
const QStringList LIST_OF_SUPPLIERS{"Omega","Intercars"};
const int COUNT_OF_XML_PRICELIST_LINES_TO_SEND = 1000;
const int PROGRESSBAR_DEVIDER = 180000; // APPROXIMATE FOR OMEGA

#endif // STATEMENTS_H
