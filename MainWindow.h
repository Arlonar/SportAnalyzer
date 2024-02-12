#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QtSql>
#include <QMessageBox>

#include "add_match.h"
#include "database.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    QPushButton *get_matches_btn;
    QPushButton *add_match_btn;

signals:

public slots:
    void get_matches_btn_click(); // show a message box
    void add_match_btn_click();
};

#endif // MAINWINDOW_H
