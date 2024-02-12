#ifndef ADD_MATCH_H
#define ADD_MATCH_H

#include <QWidget>
#include <QMessageBox>

#include "database.h"
#include "ui_add_match.h"

class AddMatch : public QWidget
{
    Q_OBJECT
public:
    explicit AddMatch(QWidget *parent = nullptr);

private:
    Ui::AddMatchForm ui;
    int current_match_id = 0;

signals:
public slots:
    void add_match_button_click();
    void add_technic_button_click();
};

#endif // ADD_MATCH_H