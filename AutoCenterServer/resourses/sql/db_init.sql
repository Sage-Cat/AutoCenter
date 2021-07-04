Table: Cars|
CREATE TABLE IF NOT EXISTS Cars (
    ID_Car      INTEGER PRIMARY KEY AUTOINCREMENT,
    Name_Car    TEXT,
    VIN         TEXT    NOT NULL,
    ID_Customer INTEGER REFERENCES Customers (ID_Customer) ON DELETE CASCADE
);


|Table: Customers|
CREATE TABLE IF NOT EXISTS Customers (
    Name_Customer TEXT,
    IBAN          TEXT    UNIQUE,
    Bank          TEXT,
    EDRPOY        TEXT    UNIQUE,
    IPN           TEXT    UNIQUE,
    Address       TEXT,
    Number        TEXT,
    Email         TEXT,
    ID_Customer   INTEGER PRIMARY KEY AUTOINCREMENT
);


|Table: Lists|
CREATE TABLE IF NOT EXISTS Lists (
    ID_List     INTEGER  PRIMARY KEY AUTOINCREMENT,
    DateTime    DATETIME DEFAULT (datetime('now', 'localtime') )
                         NOT NULL,
    ListNumber  INTEGER,
    ListType    TEXT,
    ID_Seller   INTEGER  REFERENCES Sellers (ID_Seller) ON DELETE CASCADE,
    ID_Customer INTEGER  REFERENCES Customers (ID_Customer) ON DELETE CASCADE
);



|Table: ProductTypes|
CREATE TABLE IF NOT EXISTS ProductTypes (
    Amount         INTEGER,
    ID_ProductType INTEGER PRIMARY KEY AUTOINCREMENT,
    Code           TEXT    UNIQUE ON CONFLICT REPLACE,
    Catalog        TEXT,
    TNVED          TEXT,
    Name_Product   TEXT,
    Unit           TEXT,
    Price          DOUBLE
);


|Table: Records|
CREATE TABLE IF NOT EXISTS Records (
    ID_Record      INTEGER PRIMARY KEY AUTOINCREMENT,
    Count          INTEGER,
    Price          DOUBLE,
    ID_ProductType INTEGER REFERENCES ProductTypes (ID_ProductType) ON DELETE CASCADE,
    ID_List        INTEGER REFERENCES Lists (ID_List)
);



|Table: Sellers|
CREATE TABLE IF NOT EXISTS Sellers (
    Name_Seller TEXT,
    IBAN        TEXT,
    Bank        REAL,
    EDRPOY      TEXT,
    IPN         TEXT,
    Address     TEXT,
    ID_Seller   INTEGER PRIMARY KEY AUTOINCREMENT
);


|Table: UserLogs|
CREATE TABLE IF NOT EXISTS UserLogs (
    ID_Log  INTEGER PRIMARY KEY AUTOINCREMENT,
    Message TEXT,
    ID_User INTEGER REFERENCES Users (ID_User) ON DELETE CASCADE
);



|Table: Users|
CREATE TABLE IF NOT EXISTS Users (
    ID_User   INTEGER PRIMARY KEY AUTOINCREMENT,
    Name_User TEXT,
    Number    TEXT,
    Email     TEXT,
    IPN       TEXT,
    Password  TEXT,
    isAdmin   BOOLEAN
);


|View: Customer_info|
CREATE VIEW IF NOT EXISTS Customer_info AS
    SELECT Lists.DateTime,
           Records.*
      FROM Lists
           INNER JOIN
           Records ON Lists.ID_List = Records.ID_List;


|View: UsersAndCars|
CREATE VIEW IF NOT EXISTS UsersAndCars AS
    SELECT Cars.Name_Car,
           Cars.VIN,
           Customers.*
      FROM Cars
           INNER JOIN
           Customers ON Cars.ID_Customer = Customers.ID_Customer;


|View: Statistics|
CREATE VIEW IF NOT EXISTS Statistics AS
    SELECT Lists.ID_List,
           Lists.DateTime,
           Records.Price,
           Customers.ID_Customer,
           Customers.Name_Customer
      FROM Lists
           INNER JOIN
           Records ON Lists.ID_List = Records.ID_List
           INNER JOIN
           Customers ON Lists.ID_Customer = Customers.ID_Customer;


