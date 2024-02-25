#include "change_database.h"

ChangeDatabase::ChangeDatabase(QWidget *parent) : QWidget(parent)
{
    ui.setupUi(this);
    ui.login_data_widget->hide();
    QObject::connect(ui.connect_db_button, SIGNAL(clicked()), this, SLOT(connect_database_button_click()));
}

void ChangeDatabase::connect_database_button_click()
{
    if (ui.db_combo_box->currentText() == "SQLite")
    {
        db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
        db->setDatabaseName("./data.sqlite");
        if (!db->open())
        {
            QMessageBox::critical(nullptr, "Ошибка подключения", db->lastError().text());
            qDebug() << db->lastError().text() << endl;
            return;
        }
        QSqlQuery query;
        query.exec("CREATE TABLE IF NOT EXISTS matches ("
                       "id              INTEGER PRIMARY KEY,"
                       "match_name      VARCHAR,"
                       "tournament_name VARCHAR,"
                       "date            DATE,"
                       "win             BOOL,"
                       "rating          INTEGER,"
                       "enemy_name      VARCHAR,"
                       "enemy_rating    INTEGER);"

                   "CREATE TABLE IF NOT EXISTS games ("
                       "id             INTEGER PRIMARY KEY,"
                       "match_id       INTEGER REFERENCES matches (id) NOT NULL,"
                       "number_of_game INTEGER,"
                       "win            BOOL);"

                   "CREATE TABLE IF NOT EXISTS scores ("
                       "id              INTEGER PRIMARY KEY,"
                       "game_id         INTEGER REFERENCES games (id),"
                       "number_of_score INTEGER,"
                       "win             BOOL);"

                   "CREATE TABLE IF NOT EXISTS technics ("
                       "name VARCHAR NOT NULL UNIQUE PRIMARY KEY);"

                   "CREATE TABLE IF NOT EXISTS elements ("
                       "id                INTEGER PRIMARY KEY,"
                       "score_id          INTEGER REFERENCES scores (id),"
                       "number_of_element INTEGER,"
                       "element_name      VARCHAR REFERENCES technics (name),"
                       "serve             BOOL,"
                       "your_element      BOOL,"
                       "successful        BOOL,"
                       "final_element     BOOL);");
    }
    else
    {
        db = new QSqlDatabase(QSqlDatabase::addDatabase("QPSQL"));
        db->setDatabaseName(ui.db_name_line_edit->text());
        db->setUserName(ui.db_user_line_edit->text());
        db->setPassword(ui.db_password_line_edit->text());
        db->setHostName(ui.db_host_line_edit->text());
        db->setPort(ui.db_port_line_edit->text().toInt());
        if (!db->open())
        {
            QMessageBox::critical(nullptr, "Ошибка подключения", db->lastError().text());
            qDebug() << db->lastError().text() << endl;
            return;
        }
        QSqlQuery query;
        query.exec("CREATE TABLE IF NOT EXISTS matches ("
                       "id              SERIAL PRIMARY KEY,"
                       "match_name      VARCHAR,"
                       "tournament_name VARCHAR,"
                       "date            DATE,"
                       "win             BOOL,"
                       "rating          INTEGER,"
                       "enemy_name      VARCHAR,"
                       "enemy_rating    INTEGER);"

                   "CREATE TABLE IF NOT EXISTS games ("
                       "id             SERIAL PRIMARY KEY,"
                       "match_id       INTEGER REFERENCES matches (id) NOT NULL,"
                       "number_of_game INTEGER,"
                       "win            BOOL);"

                   "CREATE TABLE IF NOT EXISTS scores ("
                       "id              SERIAL PRIMARY KEY,"
                       "game_id         INTEGER REFERENCES games (id),"
                       "number_of_score INTEGER,"
                       "win             BOOL);"

                   "CREATE TABLE IF NOT EXISTS technics ("
                       "name VARCHAR NOT NULL UNIQUE PRIMARY KEY);"

                   "CREATE TABLE IF NOT EXISTS elements ("
                       "id                SERIAL PRIMARY KEY,"
                       "score_id          INTEGER REFERENCES scores (id),"
                       "number_of_element INTEGER,"
                       "element_name      VARCHAR REFERENCES technics (name),"
                       "serve             BOOL,"
                       "your_element      BOOL,"
                       "successful        BOOL,"
                       "final_element     BOOL);");
    }

    MainWindow* window = new MainWindow();
    window->show();
    this->close();
}

void ChangeDatabase::on_db_combo_box_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "SQLite")
    {
        ui.login_data_widget->hide();
    }
    else
    {
        ui.login_data_widget->show();
    }
}

