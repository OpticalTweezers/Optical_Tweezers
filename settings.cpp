#include "Settings.h"
#include "mainwindow.h"
#include "ui_settings.h"
#include "game.h"
#include "game2.h"
#include "game3.h"
#include "game4.h"
#include "game5.h"
#include "game6.h"
#include "game7.h"
#include "game8.h"
#include "game9.h"
#include "game10.h"
#include "game11.h"
#include "game12.h"

Game*game;
Game2*game2;
Game3*game3;
Game4*game4;
Game5*game5;
Game6*game6;
Game7*game7;
Game8*game8;
Game9*game9;
Game10*game10;
Game11*game11;
Game12*game12;


Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_stage1_clicked(){
    this->hide();
    game = new Game();
    qDebug()<<"game";
    qDebug()<<game;
    game->show();

}

void Settings::on_stage2_clicked()
{
    this->hide();
    game2 = new Game2();
    game2->show();
}

void Settings::on_stage3_clicked()
{
    this->hide();
    game3 = new Game3();
    game3->show();
}

void Settings::on_stage4_clicked()
{
    this->hide();
    game4 = new Game4();
    game4->show();
}

void Settings::on_stage5_clicked()
{
    this->hide();
    game5 = new Game5();
    game5->show();
}

void Settings::on_stage6_clicked()
{
    this->hide();
    game6 = new Game6();
    game6->show();
}

void Settings::on_stage7_clicked()
{
    this->hide();
    game7 = new Game7();
    game7->show();
}

void Settings::on_stage8_clicked()
{
    this->hide();
    game8 = new Game8();
    game8->show();
}

void Settings::on_stage9_clicked()
{
    this->hide();
    game9 = new Game9();
    game9->show();
}

void Settings::on_stage10_clicked()
{
    this->hide();
    game10 = new Game10();
    game10->show();
}

void Settings::on_stage11_clicked()
{
    this->hide();
    game11 = new Game11();
    game11->show();
}

void Settings::on_stage12_clicked()
{
    this->hide();
    game12 = new Game12();
    game12->show();
}

void Settings::on_backbutton_clicked(){
    MainWindow * mainwindow = new MainWindow();
    mainwindow->show();

}
