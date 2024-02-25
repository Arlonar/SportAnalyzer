#include <QApplication>
#include <QPushButton>
#include <QtSql>

#include "change_database.h"

int main(int argc, char **argv)
{
    QApplication app (argc, argv);

    ChangeDatabase change_database(nullptr);
    change_database.show();

    return app.exec();
}
