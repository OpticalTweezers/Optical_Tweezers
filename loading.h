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
public slots:
    void finish();
private:
    Ui::Loading *ui;
    Game game;
};

#endif // LOADING_H
