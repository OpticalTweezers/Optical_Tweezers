#ifndef LOADING_H
#define LOADING_H

#include <QMainWindow>
#include "game.h"

namespace Ui {
class Loading;
}

class Loading : public QMainWindow
{
    Q_OBJECT

public:
    explicit Loading(QWidget *parent = 0);
    ~Loading();
    Game*game;
private slots:
    void progressing_change();
    void on_pushButton_clicked();

private:
    Ui::Loading *ui;
    int progressing=0;
    QTimer *timer;
};

#endif // LOADING_H
