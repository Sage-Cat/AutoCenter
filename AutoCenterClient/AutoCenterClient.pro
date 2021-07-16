QT       += core gui widgets network printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated Apis.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the Apis deprecated before Qt 6.0.0

SOURCES += \
    dialogs/addperson.cpp \
    dialogs/changelisttype.cpp \
    main.cpp \
    mainwindow.cpp \
    networkcommunication.cpp \
    tcpclient.cpp \
    widgets/info.cpp \
    widgets/lists.cpp \
    widgets/persons.cpp \
    widgets/records.cpp


HEADERS += \
    dialogs/addperson.h \
    dialogs/changelisttype.h \
    mainwindow.h \
    networkcommunication.h \
    statements.h \
    tcpclient.h \
    widgets/info.h \
    widgets/lists.h \
    widgets/persons.h \
    widgets/records.h


FORMS += \
    dialogs/addperson.ui \
    dialogs/changelisttype.ui \
    mainwindow.ui \
    widgets/info.ui \
    widgets/lists.ui \
    widgets/persons.ui \
    widgets/records.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    recources/recources.qrc

DISTFILES += \
    Tasks.txt
