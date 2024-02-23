#ifndef ADDTECHNIC_H
#define ADDTECHNIC_H

#include <QWidget>
#include <QMessageBox>

#include "database.h"
#include "ui_add_technic.h"

class AddTechnic : public QWidget
{
    Q_OBJECT
public:
    explicit AddTechnic(QWidget *parent = nullptr);
    ~AddTechnic();

private:
    Ui::AddTechnic ui;

private slots:
    void add_technic_button_click();
    void on_table_changed(QModelIndex, QModelIndex);

signals:

};

#endif // ADDTECHNIC_H
