#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include<QMediaPlaylist>
#include<QTimer>
#include"gamescene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *);
    GameScene *s=NULL;
    QTimer music;
    void playmusic();
    bool thishide;
    QMediaPlayer *player = new QMediaPlayer(this);
    QMediaPlayer *clicksound = new QMediaPlayer(this);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
