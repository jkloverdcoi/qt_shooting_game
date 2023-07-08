#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QWidget>
#include<QIcon>
#include<QTimer>
#include<QPainter>
#include <QKeyEvent>
#include <QMediaPlayer>
#include<QLabel>
#include<QFont>
#include <ctime>
#include<QSound>
#include<math.h>
#include"gamebackground.h"
#include"player.h"
#include"enemy.h"
#include"gameoverscene.h"


class GameScene : public QWidget
{
    Q_OBJECT
public:
    explicit GameScene(QWidget *parent = nullptr);
    void initialize();//初始化
    QTimer timer;//总计时器
    QTimer sec;//读秒
    QTimer halfmin;//读分钟
    int clock;//时间显示
    int rank;//难度
    int Hidth,Width;
    void GameStart();//游戏开始
    void updatePosition();//更新场景各元素坐标
    void updateInformation();//更新参数信息
    void updateRank();//更新难度
    void bonusjudge();//奖励b和残
    void paintEvent(QPaintEvent *event);//绘图
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);//键盘事件
    GameBackground background;//背景
    GameOverScene *over;
    Player player;//玩家
    int tempspeed;
    int fairyNumber;//敌机1数量
    Enemy fairy[50];//敌机1
    void showEnemy();//敌机出现
    int EnemyShowRecord;//敌机出现间隔记录
    int EnemyShowInterval;//敌机出现间隔
    void checkCollision();//碰撞检测
    void checklife();//血量检测
    bool up;//键盘按下检测
    bool down;
    bool left;
    bool right;
    bool z;//射击
    bool shift;//慢速
    bool bomb;
    bool bonus1[10];
    bool bonus2[5];
    QLabel *powerinfor=NULL;
    QLabel *timeinfor=NULL;
    Dropings powerpoint[100];
    Dropings scorepoint[200];
    int score;
    QMediaPlayer *bgm = new QMediaPlayer(this);
    QMediaPlayer *bombsound = new QMediaPlayer(this);
    QMediaPlayer *bonusound = new QMediaPlayer(this);
    QMediaPlayer *enemydefeatsound = new QMediaPlayer(this);
    QMediaPlayer *hitsound = new QMediaPlayer(this);
    QMediaPlayer *getpointsound = new QMediaPlayer(this);
    QTimer musictimer;
    void playbgm();
signals:
    void Gameover();
    void Gameclear();
    void playersafe();
    void shootbomb();

public slots:
};

#endif // GAMESCENE_H
