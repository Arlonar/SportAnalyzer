#include <QApplication>
#include <QPushButton>

#include <MainWindow.h>
#include <QtSql>

int main(int argc, char **argv)
{
    QApplication app (argc, argv);

    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:\\Users\\Artem\\Documents\\SportAnalyzer\\data.sqlite");
    if (!db.open())
    {
        qDebug() << db.lastError() << endl;
    }

    MainWindow window;
    window.show();

    return app.exec();
}
