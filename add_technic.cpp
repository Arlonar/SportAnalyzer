#include "add_technic.h"

AddTechnic::AddTechnic(QWidget *parent) : QWidget(parent)
{
    ui.setupUi(this);
    QObject::connect(ui.add_technic_button, SIGNAL(clicked()), this, SLOT(add_technic_button_click()));
    ui.techincs_table->setModel(Database::fetch_model("SELECT * FROM technics"));
}

void AddTechnic::add_technic_button_click()
{
    QString technic_name = ui.technic_name_text_edit->toPlainText();
    if (technic_name == "")
    {
        QMessageBox::critical(this, "Айайай!", "Ты давай ка тут не считай себя самым умным.\n Вводи давай название", QMessageBox::Ok);
        return;
    }
    if (Database::execute("INSERT INTO technics(name) VALUES(?)", {technic_name}))
    {
        ui.techincs_table->setModel(Database::fetch_model("SELECT * FROM technics"));
    }
}
