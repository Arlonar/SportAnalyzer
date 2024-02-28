#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "change_database.h"

int main(int argc, char **argv)
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    /*
    QApplication app (argc, argv);
    ChangeDatabase change_database;
    change_database.show();
    */

    return app.exec();
}
