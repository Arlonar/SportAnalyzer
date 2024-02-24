#include "add_match.h"

AddMatch::AddMatch(QWidget *parent) : QWidget(parent)
{
    ui.setupUi(this);
    ui.date_edit->setDate(QDate::currentDate());
    ui.add_game_widget->hide();
    ui.add_score_widget->hide();
    ui.add_element_widget->hide();

    //ui.elements_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    auto technics = Database::fetchall("SELECT * FROM technics");
    for (const auto& technic: technics)
    {
        ui.elements_combo_box->addItem(technic["name"]);
    }

    QObject::connect(ui.add_match_button, SIGNAL(clicked()), this, SLOT(add_match_button_click()));
    QObject::connect(ui.add_game_button, SIGNAL(clicked()), this, SLOT(add_game_button_click()));
    QObject::connect(ui.add_score_button, SIGNAL(clicked()), this, SLOT(add_score_button_click()));
    QObject::connect(ui.add_element_button, SIGNAL(clicked()), this, SLOT(add_element_button_click()));
}

void AddMatch::add_match_button_click()
{
    QString match_name = ui.match_name_line_edit->text();
    QString tournament_name = ui.tournament_name_line_edit->text();
    QString date = ui.date_edit->date().toString("yyyy-MM-dd");
    QString win = QString::number(ui.win_check_box->isChecked());
    QString rating = QString::number(ui.rating_spin_box->value());
    QString enemy_name = ui.enemy_name_line_edit->text();
    QString enemy_rating = QString::number(ui.enemy_rating_spin_box->value());

    Database::execute("INSERT INTO matches(match_name, tournament_name, date, win, rating, enemy_name, enemy_rating)"
                      " VALUES(?, ?, ?, ?, ?, ?, ?)", {match_name, tournament_name, date, win, rating, enemy_name, enemy_rating});
    current_match_id = Database::fetchall("SELECT id FROM matches ORDER BY id DESC LIMIT 1")[0]["id"].toInt();

    ui.add_match_widget->hide();
    ui.add_game_widget->show();
}

void AddMatch::add_game_button_click()
{
    bool win = ui.game_win_check_box->isChecked();
    int score_1 = ui.game_score_line_edit_1->text().toInt() + win;
    int score_2 = ui.game_score_line_edit_2->text().toInt() + !win;

    Database::execute("INSERT INTO games(match_id, number_of_game, win)"
                      " VALUES(?, ?, ?)", {QString::number(current_match_id),
                                           QString::number(score_1 + score_2),
                                           QString::number(win)});
    current_game_id = Database::fetchall("SELECT id FROM games ORDER BY id DESC LIMIT 1")[0]["id"].toInt();

    ui.game_score_line_edit_1->setText(QString::number(score_1));
    ui.game_score_line_edit_2->setText(QString::number(score_2));

    ui.add_score_widget->show();
    ui.add_game_widget->hide();
}

void AddMatch::add_score_button_click()
{
    bool win = ui.score_win_check_box->isChecked();
    int score_1 = ui.score_line_edit_1->text().toInt() + win;
    int score_2 = ui.score_line_edit_2->text().toInt() + !win;

    Database::execute("INSERT INTO scores(game_id, number_of_score, win) "
                      "VALUES(?, ?, ?)", {QString::number(current_game_id),
                                           QString::number(score_1 + score_2),
                                           QString::number(win)});
    current_score_id = Database::fetchall("SELECT id FROM scores ORDER BY id DESC LIMIT 1")[0]["id"].toInt();
    current_element = 1;

    ui.add_score_widget->hide();
    ui.add_element_widget->show();
    auto model = Database::fetch_table_model(("elements"), "score_id=" + QString::number(current_score_id));
    model->setHeaderData(2, Qt::Horizontal, "Номер");
    model->setHeaderData(3, Qt::Horizontal, "Название");
    model->setHeaderData(4, Qt::Horizontal, "Подача?");
    model->setHeaderData(5, Qt::Horizontal, "Твой прием?");
    model->setHeaderData(6, Qt::Horizontal, "Успешно?");
    model->setHeaderData(7, Qt::Horizontal, "Последний элемент?");
    ui.elements_table->setModel(model);
    ui.elements_table->hideColumn(0);
    ui.elements_table->hideColumn(1);

    ui.score_line_edit_1->setText(QString::number(score_1));
    ui.score_line_edit_2->setText(QString::number(score_2));
}

void AddMatch::add_element_button_click()
{
    QString serve = QString::number(ui.serve_check_box->isChecked());
    QString successful = QString::number(ui.successful_check_box->isChecked());
    QString your_element = QString::number(ui.your_element_check_box->isChecked());
    bool final_element = ui.final_element_check_box->isChecked();
    QString element_name = ui.elements_combo_box->currentText();

    QSqlTableModel* model = static_cast<QSqlTableModel*>(ui.elements_table->model());
    QSqlRecord rec = model->record();
    rec.setValue("score_id", current_score_id);
    rec.setValue("number_of_element", current_element++);
    rec.setValue("serve", serve);
    rec.setValue("element_name", element_name);
    rec.setValue("your_element", your_element);
    rec.setValue("successful", successful);
    rec.setValue("final_element", final_element);
    rec.setGenerated("id", false);
    model->insertRecord(-1, rec);

    /*
    Database::execute("INSERT INTO elements(score_id, number_of_element, serve, element_name, "
                      "your_element, successful, final_element) "
                      "VALUES(?, ?, ?, ?, ?, ?, ?)", {QString::number(current_score_id),
                                                      QString::number(current_element++),
                                                      serve, element_name, your_element,
                                                      successful, QString::number(final_element)});
    */

    if (final_element)
    {
        ui.add_element_widget->hide();

        int score_1 = ui.score_line_edit_1->text().toInt();
        int score_2 = ui.score_line_edit_2->text().toInt();

        if ((score_1 >= 11 || score_2 >= 11) && abs(score_1 - score_2) >= 2)
        {
            ui.add_game_widget->show();

            ui.score_line_edit_1->setText(QString::number(0));
            ui.score_line_edit_2->setText(QString::number(0));
        }
        else
        {
            ui.add_score_widget->show();
        }
    }
}
