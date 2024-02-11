#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QtSql>
#include <QMessageBox>

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QPushButton *get_matches_btn;
    QPushButton *add_match_btn;

    QSqlDatabase db;

signals:

public slots:
    void get_matches_btn_click(); // show a message box
    void add_match_btn_click();
};

#endif // MAINWINDOW_H
