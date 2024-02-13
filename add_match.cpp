#include "add_match.h"

AddMatch::AddMatch(QWidget *parent) : QWidget(parent)
{
    ui.setupUi(this);

    set_technic_visible(false);

    auto technics = Database::fetchall("SELECT * FROM technics");
    for (const auto& technic: technics)
    {
        ui.technics_combo_box->addItem(technic["name"]);
    }

    QObject::connect(ui.add_match_button, SIGNAL(clicked()), this, SLOT(add_match_button_click()));
    QObject::connect(ui.add_technic_button, SIGNAL(clicked()), this, SLOT(add_technic_button_click()));
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

    set_technic_visible(true);
}

void AddMatch::add_technic_button_click()
{
    QString technic = ui.technics_combo_box->currentText();
    QString successful = QString::number(ui.successful_check_box->isChecked());
    if (!Database::execute("INSERT INTO matches_technics(match_id, technic_name, successful) "
                      "VALUES(?, ?, ?)", {QString::number(current_match_id), technic, successful}))
    {
        qDebug() << "Error";
    }
    ui.techincs_table->setModel(Database::fetch_model("SELECT technic_name, successful FROM matches_technics ORDER BY id"));
}

void AddMatch::set_technic_visible(bool visible)
{
    ui.match_name_label->setVisible(!visible);
    ui.tournament_name_label->setVisible(!visible);
    ui.match_name_text_edit->setVisible(!visible);
    ui.tournament_name_text_edit->setVisible(!visible);
    ui.add_match_button->setVisible(!visible);

    ui.successful_check_box->setVisible(visible);
    ui.techincs_table->setVisible(visible);
    ui.technic_name_label->setVisible(visible);
    ui.technics_combo_box->setVisible(visible);
    ui.add_technic_button->setVisible(visible);
}
