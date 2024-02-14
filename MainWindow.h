#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QtSql>
#include <QMessageBox>

#include "add_match.h"
#include "add_technic.h"
#include "database.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    QPushButton *get_matches_button;
    QPushButton *add_match_button;
    QPushButton *set_technics_button;
    QPushButton *view_statistics_button;

signals:

private slots:
    void get_matches_button_click(); // show a message box
    void add_match_button_click();
    void set_technics_button_click();
    void view_statistics_button_click();
};

#endif // MAINWINDOW_H
