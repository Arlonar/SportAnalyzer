#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>

class Database
{
public:
    static QList<QHash<QString, QString>> fetchall(QString query_text);
    static bool execute(QString query_text, QList<QString> args = {});
};

#endif // DATABASE_H
