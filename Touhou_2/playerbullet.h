#ifndef PLAYERBULLET_H
#define PLAYERBULLET_H

#include"flyers.h"

//玩家子弹类
class PlayerBullet:public Flyers
{
public:
    PlayerBullet();
    bool free;//是否空闲
    QRect core;//判定区域
    double atk;//攻击力
    void updatePosition();//更新坐标
    void setPix(int a,int b,QString s);
};

#endif // PLAYERBULLET_H
