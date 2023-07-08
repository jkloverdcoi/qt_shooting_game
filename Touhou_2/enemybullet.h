#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include"playerbullet.h"
#include<math.h>
#define PI 3.1415926

class EnemyBullet:public PlayerBullet
{
public:
    EnemyBullet();
    QString type1pix[8];
    QString type2pix[9];
    int shootangle;//发射角度
    void updatePosition();
    void setPix(int an,int s,int pw,int ph,int a,int b,QString str);
};

#endif // ENEMYBULLET_H
