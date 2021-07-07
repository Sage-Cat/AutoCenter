Table: Cars|
CREATE TABLE IF NOT EXISTS Cars (
    ID          INTEGER PRIMARY KEY AUTOINCREMENT,
    Name_Car    TEXT,
    VIN         TEXT    NOT NULL,
    ID_Customer INTEGER REFERENCES Customers (ID) ON DELETE CASCADE
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
    ID   INTEGER PRIMARY KEY AUTOINCREMENT
);


|Table: Lists|
CREATE TABLE IF NOT EXISTS Lists (
    ID          INTEGER  PRIMARY KEY AUTOINCREMENT,
    DateTime    DATETIME DEFAULT (datetime('now', 'localtime') )
                         NOT NULL,
    ListNumber  INTEGER,
    ListType    TEXT,
    ID_Seller   INTEGER  REFERENCES Sellers (ID) ON DELETE CASCADE,
    ID_Customer INTEGER  REFERENCES Customers (ID) ON DELETE CASCADE
);



|Table: ProductTypes|
CREATE TABLE IF NOT EXISTS ProductTypes (
    Amount         INTEGER,
    ID INTEGER PRIMARY KEY AUTOINCREMENT,
    Code           TEXT    UNIQUE ON CONFLICT REPLACE,
    Catalog        TEXT,
    TNVED          TEXT,
    Name_Product   TEXT,
    Unit           TEXT,
    Price          DOUBLE
);


|Table: Records|
CREATE TABLE IF NOT EXISTS Records (
    ID             INTEGER PRIMARY KEY AUTOINCREMENT,
    Count          INTEGER,
    Price          DOUBLE,
    ID_ProductType INTEGER REFERENCES ProductTypes (ID) ON DELETE CASCADE,
    ID_List        INTEGER REFERENCES Lists (ID)
);




|Table: Sellers|
CREATE TABLE IF NOT EXISTS Sellers (
    Name_Seller TEXT,
    IBAN        TEXT,
    Bank        REAL,
    EDRPOY      TEXT,
    IPN         TEXT,
    Address     TEXT,
    ID   INTEGER PRIMARY KEY AUTOINCREMENT
);


|Table: UserLogs|
CREATE TABLE IF NOT EXISTS UserLogs (
    ID      INTEGER PRIMARY KEY AUTOINCREMENT,
    Message TEXT,
    ID_User INTEGER REFERENCES Users (ID) ON DELETE CASCADE
);


|Table: Users|
CREATE TABLE IF NOT EXISTS Users (
    ID   INTEGER PRIMARY KEY AUTOINCREMENT,
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
           Records ON Lists.ID = Records.ID_List;


|View: UsersAndCars|
CREATE VIEW IF NOT EXISTS UsersAndCars AS
    SELECT Cars.Name_Car,
           Cars.VIN,
           Customers.*
      FROM Cars
           INNER JOIN
           Customers ON Cars.ID_Customer = Customers.ID;


|View: Statistics|
CREATE VIEW IF NOT EXISTS Statistics AS
    SELECT Lists.ID_List,
           Lists.DateTime,
           Records.Price,
           Customers.ID_Customer,
           Customers.Name_Customer
      FROM Lists
           INNER JOIN
           Records ON Lists.ID = Records.ID_List
           INNER JOIN
           Customers ON Lists.ID_Customer = Customers.ID;

|View: Lists_view|
CREATE VIEW IF NOT EXISTS Lists_view AS
    SELECT Lists.DateTime,
           Lists.ListNumber,
           Lists.ListType,
           Sellers.Name_Seller,
           Customers.Name_Customer,
           Lists.ID,
           Customers.IPN
      FROM Lists
           LEFT JOIN
           Sellers ON Lists.ID_Seller = Sellers.ID
           LEFT JOIN
           Customers ON Lists.ID_Customer = Customers.ID;

|View: Records_view|
CREATE VIEW IF NOT EXISTS Records_view AS
    SELECT ProductTypes.Code,
           ProductTypes.Catalog,
           ProductTypes.TNVED,
           ProductTypes.Name_Product,
           ProductTypes.Unit,
           Records.Count,
           Records.Price,
           Records.ID_List
      FROM Records
           LEFT JOIN
           ProductTypes ON Records.ID_ProductType = ProductTypes.ID;





