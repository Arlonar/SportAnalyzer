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

QList<QHash<QString, QString>> Database::fetchall(QString query_text)
{
    QSqlQuery query(query_text);
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

QSqlTableModel* Database::fetch_table_model(QString table_name, QList<QString> columns)
{
    QSqlTableModel* model = new QSqlTableModel;
    model->setTable(table_name);
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    for (int i = 0; i < columns.size(); ++i)
    {
        model->setHeaderData(0, Qt::Horizontal, columns[i]);
    }
    return model;
}
