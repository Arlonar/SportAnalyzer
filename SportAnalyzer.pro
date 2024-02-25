TARGET = SportAnalyzer

QT = core gui widgets sql

TEMPLATE = app

greaterThan(QT_MAJOR_VERSION, 4):QT += widgets

SOURCES += \
    MainWindow.cpp \
    add_match.cpp \
    add_technic.cpp \
    change_database.cpp \
    main.cpp \
    statistic.cpp

HEADERS += \
    MainWindow.h \
    add_match.h \
    add_technic.h \
    change_database.h \
    statistic.h

DISTFILES += \
    data.sqlite

FORMS += \
    add_match.ui \
    add_technic.ui \
    change_database.ui \
    statistic.ui
