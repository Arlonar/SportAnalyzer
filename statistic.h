#ifndef STATISTIC_H
#define STATISTIC_H

#include <QWidget>

namespace Ui {
class Statistic;
}

class Statistic : public QWidget
{
    Q_OBJECT

public:
    explicit Statistic(QWidget *parent = nullptr);
    ~Statistic();

private:
    Ui::Statistic *ui;
};

#endif // STATISTIC_H
