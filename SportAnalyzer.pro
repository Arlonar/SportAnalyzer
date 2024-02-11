TARGET = SportAnalyzer

QT = core gui widgets sql

TEMPLATE = app

greaterThan(QT_MAJOR_VERSION, 4):QT += widgets

SOURCES += \
    MainWindow.cpp \
    main.cpp

HEADERS += \
    MainWindow.h

DISTFILES += \
    data.db
