#include <Game.h>
#include <Mainwindow.h>
#include <QApplication>
extern Game *game;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return a.exec();

}

