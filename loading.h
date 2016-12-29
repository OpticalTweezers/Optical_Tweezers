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
private slots:
    void progressing_change();
private:
    Ui::Loading *ui;
    Game * game;
    int progressing=0;
};

#endif // LOADING_H
