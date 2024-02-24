#include "database.h"

bool Database::execute(QString query_text, QList<QString> args)
{
    QSqlQuery query;
    query.prepare(query_text);
    for (int i = 0; i < args.size(); ++i)
    {
        query.bindValue(i, args[i]);
    }
    return query.exec();
}

QList<QHash<QString, QString>> Database::fetchall(QString query_text, QList<QString> args)
{
    QSqlQuery query(query_text);
    for (int i = 0; i < args.size(); ++i)
    {
        query.bindValue(i, args[i]);
    }
    QList<QHash<QString, QString>> result;
    while (query.next())
    {
        QSqlRecord record = query.record();
        QHash<QString, QString> element;
        for (int i = 0; i < record.count(); ++i)
        {
            element[record.fieldName(i)] = record.value(i).toString();
        }
        result.append(element);
    }
    return result;
}

QSqlQueryModel* Database::fetch_model(QString query_text)
{
    QSqlQuery query(query_text);
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(query);
    return model;
}

QSqlTableModel* Database::fetch_table_model(QString table_name, QString filter)
{
    QSqlTableModel* model = new QSqlTableModel;
    model->setTable(table_name);
    model->setFilter(filter);
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    return model;
}
