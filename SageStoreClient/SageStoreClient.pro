QT       += core gui widgets network printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    qdialogs/authorization.cpp \
    qdialogs/load_supplier_invoice.cpp \
    qdialogs/load_supplier_pricelist.cpp \
    qdialogs/new_customer.cpp \
    qdialogs/new_seller.cpp \
    qdialogs/print_barcode.cpp \
    qdialogs/print_document.cpp \
    qdialogs/registration.cpp \
    qwidgets/customer_info.cpp \
    qwidgets/customers.cpp \
    qwidgets/inventory.cpp \
    qwidgets/lists.cpp \
    qwidgets/records.cpp \
    qwidgets/sellers.cpp \
    qwidgets/statistics.cpp \
    qwidgets/user_logs.cpp \
    qwidgets/users.cpp \
    tcpclient.cpp


HEADERS += \
    mainwindow.h \
    qdialogs/authorization.h \
    qdialogs/load_supplier_invoice.h \
    qdialogs/load_supplier_pricelist.h \
    qdialogs/new_customer.h \
    qdialogs/new_seller.h \
    qdialogs/print_barcode.h \
    qdialogs/print_document.h \
    qdialogs/registration.h \
    qwidgets/customer_info.h \
    qwidgets/customers.h \
    qwidgets/inventory.h \
    qwidgets/lists.h \
    qwidgets/records.h \
    qwidgets/sellers.h \
    qwidgets/statistics.h \
    qwidgets/user_logs.h \
    qwidgets/users.h \
    statements.h \
    tcpclient.h


FORMS += \
    mainwindow.ui \
    qdialogs/authorization.ui \
    qdialogs/load_supplier_invoice.ui \
    qdialogs/load_supplier_pricelist.ui \
    qdialogs/new_customer.ui \
    qdialogs/new_seller.ui \
    qdialogs/print_barcode.ui \
    qdialogs/print_document.ui \
    qdialogs/registration.ui \
    qwidgets/customer_info.ui \
    qwidgets/customers.ui \
    qwidgets/inventory.ui \
    qwidgets/lists.ui \
    qwidgets/records.ui \
    qwidgets/sellers.ui \
    qwidgets/statistics.ui \
    qwidgets/user_logs.ui \
    qwidgets/users.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    recources/recources.qrc

DISTFILES +=
