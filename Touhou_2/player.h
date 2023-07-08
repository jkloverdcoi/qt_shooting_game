#ifndef PLAYER_H
#define PLAYER_H

#include"flyers.h"
#include"playerbullet.h"
//玩家类
class Player:public Flyers
{
public:
    Player();
    void updateBulletPos(PlayerBullet b[]);
    QRect core;//判定点区域
    QPixmap corePix;
    QPixmap pixs;
    PlayerBullet type1Left[30];//子弹
    PlayerBullet type1Right[30];
    PlayerBullet type2Left[30];
    PlayerBullet type2Right[30];
    PlayerBullet type3Left[30];
    PlayerBullet type3Right[30];
    Flyers Wingman[4];//僚机
    int shootRecord;//发射间隔记录
    int shootInterval;//发射间隔记录
    int life;//残机数
    int bomb;//炸弹数
    double power;
    bool safe;//无敌状态
    void setPosition();
    void shoot();//发射子弹
    void shootbullet(PlayerBullet b[],int x);
    void hit();//被弹
};

#endif // PLAYER_H
