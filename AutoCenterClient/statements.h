#ifndef STATEMENTS_H
#define STATEMENTS_H

#include <QString>
#include <QVector>
#include <QStringList>
#include <QHostAddress>
#include <QMessageBox>
#include <QDebug>

//! List[N][M], where
//! N - number of rows,
//! M - number of columns
typedef std::vector<QStringList> RecordsList;

enum OperationType {
    sale = 0,
    receipt
};
const QStringList LISTTYPE_NAMES = {
    ""
    "Рахунок",
    "Видаткова накладна",
    "Товарний чек",
    "Податкова накладна",
    "Накладна на повернення",
    "Накладна на надходження"
};

// TCP Connection
const QHostAddress DEFAULT_HOSTNAME = QHostAddress::LocalHost;
const int DEFAULT_PORT = 9999;
const int DEFAULT_TIMEOUT_MS = 5000;

//! All delimiters for transfering data (decode messages using it in direct 0,1... order)
const QStringList DELIMITERS{":::", "|||"};
enum delims {
    primary = 0,
    secondary
};

//! All types of requests that could be handled by the server
const QStringList SERVER_API{
    "add",
    "del",
    "edit",
    "get",
    "login",
    "statistics",
    "pricelist"
};
enum ServerAPI {
    records_add = 0,
    records_delete,
    records_edit,
    records_get,
    login,
    stat,
    pricelist
};

//! All database tables
const QStringList DATABASE_TABLES{
    "Cars",
    "Customers",
    "Lists",
    "Products",
    "Records",
    "Sellers",
    "UserLogs",
    "Users",

     /* Views */
    "Customer_info",
    "Lists_view",
    "Statistics",
    "UsersAndCars",
    "Records_view",
    "Max_ListNumber"
};
enum Tables {
    cars = 0,
    customers,
    lists,
    products,
    records,
    sellers,
    user_logs,
    users,

    /* Views */
    customers_info,
    lists_view,
    statistics,
    users_and_cars,
    records_view,
    max_listnumber
};

//// Customers & Sellers
//const QStringList CUSTOMERS_COLUMNS_NAMES{"Ім'я", "IBAN", "Банк", "ЄДРПОУ", "ІПН", "Адреса", "Телефон", "Ел. пошта", "ID"};
//const QStringList SELLERS_COLUMNS_NAMES{"Ім'я", "IBAN", "Банк", "ЄДРПОУ", "ІПН", "Адреса", "ID"};

//! Lists
const QStringList LISTS_COLUMNS_NAMES{
    "Коли",         "Номер документа",  "Вид",
    "Продавець",    "Покупець",         "ID",
    "IPN"
};
// table
const int TABLE_LISTS_DATETIME_INDEX = 1;
const int TABLE_LISTS_SELLER_INDEX = 4;
const int TABLE_LISTS_CUSTOMER_INDEX = 5;
// view
const int VIEW_LISTS_LISTTYPE_INDEX = 2;
const int VIEW_LISTS_ID_INDEX = 5;
const int VIEW_LISTS_IPN_INDEX = 6;

//! Records
const QStringList RECORDS_COLUMNS_NAMES{
    "Код",             "Каталожний номер",     "Код ТНВЕД",
    "Назва",           "Одиниці",              "Кількість",
    "Ціна",            "ID_List",              "ID",
    "ID_Product"
};
// view
const int VIEW_RECORDS_CODE_INDEX = 0;
const int VIEW_RECORDS_COUNT_INDEX = 5;
const int VIEW_RECORDS_PRICE_INDEX = 6;
const int VIEW_RECORDS_IDLIST_INDEX = 7;
const int VIEW_RECORDS_ID_INDEX = 8;
const int VIEW_RECORDS_IDPRODUCT_INDEX = 9;

//! Customers
const int TABLE_CUSTOMERS_NAMES_INDEX = 0;
const int TABLE_CUSTOMERS_ID_INDEX = 8;

//! Sellers
const int TABLE_SELLERS_NAMES_INDEX = 0;
const int TABLE_SELLERS_ID_INDEX = 6;

//! ProductTypes
const int TABLE_PRODUCTS_ID_INDEX = 0;

//// Inventory
//const QStringList INVENTORY_COLUMNS_NAMES{"Кількість", "", "Код",  "Каталожний номер", "Код ТНВЕД", "Назва", "Одиниці", ""};

//// XML pricelist's lines sending
//const QStringList LIST_OF_SUPPLIERS{"Omega","Intercars"};
//const int COUNT_OF_XML_PRICELIST_LINES_TO_SEND = 1000;
//const int PROGRESSBAR_DEVIDER = 180000; // APPROXIMATE FOR OMEGA

#endif // STATEMENTS_H
