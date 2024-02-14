#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    setFixedSize(1280, 720);

    get_matches_button = new QPushButton("Посмотреть список всех матчей", this);
    get_matches_button->setGeometry(100, 100, 200, 100);

    add_match_button = new QPushButton("Добавить матч", this);
    add_match_button->setGeometry(400, 100, 200, 100);

    set_technics_button = new QPushButton("Изменить техники", this);
    set_technics_button->setGeometry(700, 100, 200, 100);

    view_statistics_button = new QPushButton("Посмотреть статистику", this);
    view_statistics_button->setGeometry(1000, 100, 200, 100);

    QObject::connect(get_matches_button, SIGNAL(clicked()), this, SLOT(get_matches_button_click()));
    QObject::connect(add_match_button, SIGNAL(clicked()), this, SLOT(add_match_button_click()));
    QObject::connect(set_technics_button, SIGNAL(clicked()), this, SLOT(set_technics_button_click()));
    QObject::connect(view_statistics_button, SIGNAL(clicked()), this, SLOT(view_statistics_button_click()));
}

void MainWindow::get_matches_button_click()
{
    auto matches_info = Database::fetchall("SELECT * FROM matches");
    QString result;
    for (int i = 0; i < matches_info.size(); ++i)
    {
        QString match_name = matches_info[i]["match_name"];
        QString tournament_name = matches_info[i]["tournament_name"];
        result += QString::number(i + 1) + ". " + match_name + " " + tournament_name + "\n";
    }
    QMessageBox::question(this, "test", result, QMessageBox::Ok);
}

void MainWindow::add_match_button_click()
{
    QWidget* add_match;
    add_match = new AddMatch();
    add_match->show();
}

void MainWindow::set_technics_button_click()
{
    QWidget* add_technic;
    add_technic = new AddTechnic();
    add_technic->show();
}

void MainWindow::view_statistics_button_click()
{
    QMessageBox::question(this, "test", "Comming soon", QMessageBox::Ok);
}
