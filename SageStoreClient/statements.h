#ifndef STATEMENTS_H
#define STATEMENTS_H

#include <QString>
#include <QVector>
#include <QStringList>

//! List[N][M], where
//! N - number of rows,
//! M - number of columns
typedef std::vector<QStringList> RecordsList;

enum doc_type {
    sale = 0,
    receipt
};

// TCP Connection
//const QString DEFAULT_HOSTNAME = "google.com";
//const int DEFAULT_PORT = 80;
//const QStringList DELIMITERS{":::", "|||"};

//// Customers & Sellers
//const QStringList CUSTOMERS_COLUMNS_NAMES{"Ім'я", "IBAN", "Банк", "ЄДРПОУ", "ІПН", "Адреса", "Телефон", "Ел. пошта", "ID"};
//const QStringList SELLERS_COLUMNS_NAMES{"Ім'я", "IBAN", "Банк", "ЄДРПОУ", "ІПН", "Адреса", "ID"};

//// Lists & Records
//const QStringList LISTS_COLUMNS_NAMES{"Коли", "Номер документа", "Продавець", "Покупець"};
//const QStringList RECORDS_COLUMNS_NAMES{"Код", "Каталожний номер", "Код ТНВЕД", "Назва", "Одиниці", "Кількість", "Ціна"};

//// Inventory
//const QStringList INVENTORY_COLUMNS_NAMES{"Кількість", "", "Код",  "Каталожний номер", "Код ТНВЕД", "Назва", "Одиниці", ""};

//// XML pricelist's lines sending
//const QStringList LIST_OF_SUPPLIERS{"Omega","Intercars"};
//const int COUNT_OF_XML_PRICELIST_LINES_TO_SEND = 1000;
//const int PROGRESSBAR_DEVIDER = 180000; // APPROXIMATE FOR OMEGA

#endif // STATEMENTS_H
