#ifndef STATEMENTS_H
#define STATEMENTS_H

#include <QString>
#include <QVector>
#include <QStringList>
#include <QHostAddress>
#include <QMessageBox>
#include <QDebug>
#include <QMap>

//! List[N][M], where
//! N - number of rows,
//! M - number of columns
typedef std::vector<QStringList> RecordsList;

const int ERROR_CODE = -1;

enum OperationType {
    sale = 0,
    receipt
};

enum ListTypes {
    // SALE
    default_list = 0,
    invoice,
    sales_invoice,
    sales_receipt,
    tax_invoice,
    return_invoice,

    // RECEIPT
    receipt_invoice
};

const QMap<ListTypes, QString> LIST_TYPES = {
    // SALE
    {ListTypes::default_list, ""},
    {ListTypes::invoice, "Рахунок"},
    {ListTypes::sales_invoice, "Видаткова накладна"},
    {ListTypes::sales_receipt, "Товарний чек"},
    {ListTypes::tax_invoice, "Податкова накладна"},
    {ListTypes::return_invoice, "Накладна на повернення"},

    // RECEIPT
    {ListTypes::receipt_invoice, "Накладна на надходження"}
};

// TCP Connection
const QHostAddress DEFAULT_HOSTNAME = QHostAddress::LocalHost;
const int DEFAULT_PORT = 9999;
const int DEFAULT_TIMEOUT_MS = 5000;

//! All delimiters for transfering data (decode messages using it in direct 0,1... order)
enum Delimiters {
    primary = 0,
    secondary
};

const QMap<Delimiters, QString> DELIMITERS = {
    {Delimiters::primary, ":::"},
    {Delimiters::secondary, "|||"}
};

//! All types of requests that could be handled by the server
enum Api {
    _add = 0,
    _del,
    _edit,
    _get,
    login,
    stat,
    pricelist
};

const QMap<Api, QString> SERVER_API = {
    {Api::_add, "add"},
    {Api::_del, "del"},
    {Api::_edit, "edit"},
    {Api::_get, "get"},
    {Api::login, "login"},
    {Api::stat, "statistics"},
    {Api::pricelist, "pricelist"}
};

//! All database tables & views
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
    view_lists,
    view_records,
    view_customer_cars,

    info_customer,
    info_user,
    max_list_number,
    statistics,

};

const QMap<Tables, QString> DATABASE_TABLES = {
    {Tables::cars, "Cars"},
    {Tables::customers, "Customers"},
    {Tables::lists, "Lists"},
    {Tables::products, "Products"},
    {Tables::records, "Records"},
    {Tables::sellers, "Sellers"},
    {Tables::user_logs, "UserLogs"},
    {Tables::users, "Users"},

     /* Views */
    {Tables::view_lists, "view_Lists"},
    {Tables::view_records, "view_Records"},
    {Tables::view_customer_cars, "view_CustomerCars"},
    {Tables::info_customer, "info_Customer"},
    {Tables::info_user, "info_User"},
    {Tables::max_list_number, "max_ListNumber"},
    {Tables::statistics, "Statistics"}
};

//// Customers & Sellers
//const QStringList CUSTOMERS_COLUMNS_NAMES{"Ім'я", "IBAN", "Банк", "ЄДРПОУ", "ІПН", "Адреса", "Телефон", "Ел. пошта", "ID"};
//const QStringList SELLERS_COLUMNS_NAMES{"Ім'я", "IBAN", "Банк", "ЄДРПОУ", "ІПН", "Адреса", "ID"};


const QMap<Tables, QStringList> COLUMN_NAMES = {
    {
        Tables::sellers,
        {
            "Ім'я", "IBAN", "Банк",
            "ЄДРПОУ", "ІПН", "Адреса",
            "ID"
        }
    },
    {
        Tables::customers,
        {
            "Ім'я", "IBAN", "Банк",
            "ЄДРПОУ", "ІПН", "Адреса",
            "Телефон", "Ел. пошта", "ID"
        }
    },
    {
        Tables::users,
        {
            "Ім'я", "Телефон", "Ел. пошта",
            "ІПН", "Пароль", "ID"
        }
    },
    {
        Tables::info_customer,
        {
            "Коли", "Код", "Каталог",
            "ТНВЕД", "Назва", "Одиниці",
            "К-сть", "Ціна", "ID"
        }
    },
    {
        Tables::info_user,
        {
            "Коли", "Що зробив(ла)", "ID"
        }
    },
    {
        Tables::view_lists,
        {
            "Коли",         "Номер документа",  "Вид",
            "Продавець",    "Покупець",         "ID",
            "IPN"
        }
    },
    {
        Tables::view_records,
        {
            "Код",             "Каталожний номер",     "Код ТНВЕД",
            "Назва",           "Одиниці",              "Кількість",
            "Ціна",            "ID_List",              "ID",
            "ID_Product"
        }
    }
};

const QMap<Tables, int> COLUMN_ID_INDEX = {
    {Tables::info_customer, 0},
    {Tables::info_user, 0},
    {Tables::customers, 0},
    {Tables::sellers, 0},
    {Tables::users, 0},
    {Tables::products, 0},

    /* VIEWS */
    {Tables::view_lists, 5},
    {Tables::view_records, 8}
};

//! Lists
// table
const int TABLE_LISTS_DATETIME_INDEX = 1;
const int TABLE_LISTS_SELLER_INDEX = 4;
const int TABLE_LISTS_CUSTOMER_INDEX = 5;
// view
const int VIEW_LISTS_LISTTYPE_INDEX = 2;
const int VIEW_LISTS_IPN_INDEX = 6;

//! Records
// view
const int VIEW__CODE_INDEX = 0;
const int VIEW__COUNT_INDEX = 5;
const int VIEW__PRICE_INDEX = 6;
const int VIEW__IDLIST_INDEX = 7;
const int VIEW__IDPRODUCT_INDEX = 9;

//! Customers
const int TABLE_CUSTOMERS_NAMES_INDEX = 0;

//! Sellers
const int TABLE_SELLERS_NAMES_INDEX = 0;

//// Inventory
//const QStringList INVENTORY_COLUMNS_NAMES{"Кількість", "", "Код",  "Каталожний номер", "Код ТНВЕД", "Назва", "Одиниці", ""};

//// XML pricelist's lines sending
//const QStringList LIST_OF_SUPPLIERS{"Omega","Intercars"};
//const int COUNT_OF_XML_PRICELIST_LINES_TO_SEND = 1000;
//const int PROGRESSBAR_DEVIDER = 180000; // APPROXIMATE FOR OMEGA

#endif // STATEMENTS_H
