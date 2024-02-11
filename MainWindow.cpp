#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    setFixedSize(1280, 720);

    get_matches_btn = new QPushButton("Посмотреть список всех матчей", this);
    get_matches_btn->setGeometry(100, 100, 200, 100);

    add_match_btn = new QPushButton("Добавить матч", this);
    add_match_btn->setGeometry(400, 100, 200, 100);

    QObject::connect(get_matches_btn, SIGNAL(clicked()), this, SLOT(get_matches_btn_click()));
    QObject::connect(add_match_btn, SIGNAL(clicked()), this, SLOT(add_match_btn_click()));

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:\\Users\\Artem\\Documents\\SportAnalyzer\\data.sqlite");
    if (!db.open())
    {
        qDebug() << db.lastError() << endl;
    }
    else
    {
        qDebug() << "Connection to Database successful" << endl;
    }
}

MainWindow::~MainWindow()
{
    db.close();
}

void MainWindow::get_matches_btn_click()
{
    QSqlQuery query("SELECT * FROM matches");
    if (!query.exec())
    {
        qDebug() << db.lastError() << endl;
    }
    QString result;
    while (query.next())
    {
        QString match_name = query.value(query.record().indexOf("match_name")).toString();
        QString tournament_name = query.value(query.record().indexOf("tournament_name")).toString();
        result += match_name + " " + tournament_name + "\n";
    }
    QMessageBox::question(this, "test", result, QMessageBox::Ok);
}

void MainWindow::add_match_btn_click()
{
    QMessageBox::question(this, "test", "test", QMessageBox::Ok);
}
