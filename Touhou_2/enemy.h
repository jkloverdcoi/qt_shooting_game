#ifndef ENEMY_H
#define ENEMY_H

#include"flyers.h"
#include"enemybullet.h"
#include"dropings.h"
#include"playerbullet.h"

class Enemy:public Flyers
{
public:
    Enemy();
    bool free;
    QRect core;//判定区域
    void updatePosition();//更新坐标
    void updateChildPosition();//更新子物件坐标
    QString fairypix[6];
    EnemyBullet bullet[10];
    int life;
    int bulletnumber;
    int powernum;
    int shootRecord;//发射间隔记录
    int shootInterval;//发射间隔记录
    void shoot();//发射子弹
    void droppowerpoint(Dropings &p);//掉落P点
    void hit(PlayerBullet b[],int n);
};

#endif // ENEMY_H
