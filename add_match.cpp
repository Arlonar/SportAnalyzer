#include "add_match.h"

AddMatch::AddMatch(QWidget *parent) : QWidget(parent)
{
    ui.setupUi(this);
    ui.techincs_table->hide();
    ui.add_technics_button->hide();

    QObject::connect(ui.add_match_button, SIGNAL(clicked()), this, SLOT(add_match_button_click()));
    QObject::connect(ui.add_technics_button, SIGNAL(clicked()), this, SLOT(add_technic_button_click()));
}

void AddMatch::add_match_button_click()
{
    QString match_name = ui.match_name_text_edit->toPlainText();
    QString tournament_name = ui.tournament_name_text_edit->toPlainText();
    if (match_name == "" and tournament_name == "")
    {
        QMessageBox::critical(this, "Неправильно", "Ты че ёпта!\nЗаполни хотя бы название турнира", QMessageBox::Ok);
        return;
    }
    Database::execute("INSERT INTO matches(match_name, tournament_name) VALUES(?, ?)", {match_name, tournament_name});

    current_match_id = Database::fetchall("SELECT id FROM matches ORDER BY id DESC LIMIT 1")[0]["id"].toInt();

    ui.techincs_table->show();
    ui.add_technics_button->show();

    ui.add_match_button->hide();
    ui.match_name_label->hide();
    ui.match_name_text_edit->hide();
    ui.tournament_name_label->hide();
    ui.tournament_name_text_edit->hide();
}

void AddMatch::add_technic_button_click()
{
    QMessageBox::information(this, "В разработке", "В разработке", QMessageBox::Ok);
}
