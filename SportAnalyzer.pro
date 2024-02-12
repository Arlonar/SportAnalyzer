TARGET = SportAnalyzer

QT = core gui widgets sql

TEMPLATE = app

greaterThan(QT_MAJOR_VERSION, 4):QT += widgets

SOURCES += \
    MainWindow.cpp \
    add_match.cpp \
    database.cpp \
    main.cpp

HEADERS += \
    MainWindow.h \
    add_match.h \
    database.h

DISTFILES += \
    data.sqlite

FORMS += \
    add_match.ui
