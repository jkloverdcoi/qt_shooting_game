#ifndef GAMEOVERSCENE_H
#define GAMEOVERSCENE_H

#include <QWidget>
#include<QPainter>
#include<QIcon>
#include<QPushButton>
#include<QMediaPlayer>
#include<QLabel>
#include<QFont>
#include<QDebug>
#include<QTimer>

class GameOverScene : public QWidget
{
    Q_OBJECT
public:
    explicit GameOverScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    QPushButton *back=NULL;
    QPushButton *quit=NULL;
    QLabel *infor=NULL;//分数显示
    void showscore(int a);
    bool win=true;
    QMediaPlayer *gameoverbgm = new QMediaPlayer(this);
    QMediaPlayer *gameclearbgm = new QMediaPlayer(this);
    QMediaPlayer *clicksound = new QMediaPlayer(this);
    QTimer musictimerwin;
    QTimer musictimerlose;
    void playbgm();
signals:
    void backtomenu();
public slots:
};

#endif // GAMEOVERSCENE_H
