#include "add_technic.h"

AddTechnic::AddTechnic(QWidget *parent) : QWidget(parent)
{
    ui.setupUi(this);
    QObject::connect(ui.add_technic_button, SIGNAL(clicked()), this, SLOT(add_technic_button_click()));

    ui.techincs_table->setModel(Database::fetch_table_model("technics"));
    ui.techincs_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui.techincs_table->hideColumn(1);
}

void AddTechnic::add_technic_button_click()
{
    QString technic_name = ui.technic_name_text_edit->toPlainText();
    if (technic_name == "")
    {
        QMessageBox::critical(this, "Айайай!", "Ты давай ка тут не считай себя самым умным.\n Вводи давай название", QMessageBox::Ok);
        return;
    }
    QSqlTableModel* model = static_cast<QSqlTableModel*>(ui.techincs_table->model());
    QSqlRecord rec = model->record();
    rec.setValue("name", technic_name);
    model->insertRecord(-1, rec);
}

void AddTechnic::on_table_changed(QModelIndex top_left, QModelIndex bottom_right)
{
    qDebug() << "test";
    if (top_left.isValid() && bottom_right.isValid()) {
        int row = top_left.row();
        int column = top_left.column();

        // Получаем модель данных
        QAbstractItemModel* model = ui.techincs_table->model();

        // Получаем количество колонок
        int columnCount = model->columnCount();

        // Выводим данные всех остальных колонок этой строки
        for (int col = 0; col < columnCount; ++col) {
            if (col != column) {
                QVariant data = model->data(model->index(row, col));
                qDebug() << data.toString();
            }
        }
    }
}
