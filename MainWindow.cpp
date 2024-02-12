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
}

void MainWindow::get_matches_btn_click()
{
    auto matches_info = Database::fetchall("SELECT * FROM matches");
    QString result;
    for (int i = 0; i < matches_info.size(); ++i)
    {
        QString match_name = matches_info[i]["match_name"];
        QString tournament_name = matches_info[i]["tournament_name"];
        result += match_name + " " + tournament_name + "\n";
    }
    QMessageBox::question(this, "test", result, QMessageBox::Ok);
}

void MainWindow::add_match_btn_click()
{
    QWidget* add_match;
    add_match = new AddMatch();
    add_match->show();
    // QMessageBox::question(this, "test", "test", QMessageBox::Ok);
}
