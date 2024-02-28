#ifndef CHANGEDATABASE_H
#define CHANGEDATABASE_H

#include <QWidget>

#include "ui_change_database.h"
#include "MainWindow.h"

class ChangeDatabase : public QWidget
{
    Q_OBJECT
public:
    explicit ChangeDatabase(QWidget *parent = nullptr);

private:
    Ui::DBWindow ui;
    QSqlDatabase* db;

private slots:
    void connect_database_button_click();

    void on_db_combo_box_currentTextChanged(const QString &arg1);

signals:

};

#endif // CHANGEDATABASE_H
