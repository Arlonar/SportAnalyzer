#ifndef ADDTECHNIC_H
#define ADDTECHNIC_H

#include <QWidget>
#include <QMessageBox>
#include <QtSql>

#include "ui_add_technic.h"

class AddTechnic : public QWidget
{
    Q_OBJECT
public:
    explicit AddTechnic(QWidget *parent = nullptr);

private:
    Ui::AddTechnic ui;

private slots:
    void add_technic_button_click();
    void delete_technic_button_click();

signals:

};

#endif // ADDTECHNIC_H
