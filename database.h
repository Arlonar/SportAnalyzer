#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>

class Database
{
public:
    static QList<QHash<QString, QString>> fetchall(QString query_text);
    static bool execute(QString query_text, QList<QString> args = {});
    static QSqlQueryModel* fetch_model(QString query_text);
};

#endif // DATABASE_H
