#include "add_technic.h"

AddTechnic::AddTechnic(QWidget *parent) : QWidget(parent)
{
    ui.setupUi(this);
    QObject::connect(ui.add_technic_button, SIGNAL(clicked()), this, SLOT(add_technic_button_click()));
    QObject::connect(ui.delete_technic_button, SIGNAL(clicked()), this, SLOT(delete_technic_button_click()));

    QSqlTableModel* model = new QSqlTableModel;
    model->setTable("technics");
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);

    ui.techincs_table->setModel(model);
    ui.techincs_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void AddTechnic::add_technic_button_click()
{
    QString technic_name = ui.technic_name_text_edit->toPlainText();
    if (technic_name == "")
    {
        QMessageBox::critical(this, "Error", "Введи название", QMessageBox::Ok);
        return;
    }
    QSqlTableModel* model = static_cast<QSqlTableModel*>(ui.techincs_table->model());
    QSqlRecord rec = model->record();
    rec.setValue("name", technic_name);
    model->insertRecord(-1, rec);
}

void AddTechnic::delete_technic_button_click()
{
    QModelIndexList selected_indexes = ui.techincs_table->selectionModel()->selectedIndexes();
    if (selected_indexes.isEmpty())
    {
        QMessageBox::critical(this, "Error", "Выбери элемент", QMessageBox::Ok);
        return;
    }
    static_cast<QSqlTableModel*>(ui.techincs_table->model())->removeRow(selected_indexes.first().row());
}
