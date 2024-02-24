#ifndef ADD_MATCH_H
#define ADD_MATCH_H

#include <QWidget>
#include <QMessageBox>
#include <QTableView>

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
    int current_game_id = 0;
    int current_score_id = 0;
    int current_element = 1;

signals:
private slots:
    void add_match_button_click();
    void add_game_button_click();
    void add_score_button_click();
    void add_element_button_click();
};

#endif // ADD_MATCH_H
