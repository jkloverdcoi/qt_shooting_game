#include "playerbullet.h"

PlayerBullet::PlayerBullet()
{
    X=0;
    Y=0;
    speed=15;
    PixSizeH=70;
    PixSizeW=30;
    pix.load(":/res/a01.png");
    pix=pix.scaled(PixSizeW,PixSizeH);
    core.setHeight(PixSizeH);
    core.setWidth(PixSizeW);
    core.moveTo(X,Y);
    free=true;
    atk=20;
}

void PlayerBullet::updatePosition()
{
    if(free==true){
        return;
    }
    else{
        Y-=speed;
        core.moveTo(X,Y);
        if(Y<=0){
            free=true;
        }
    }
}

void PlayerBullet::setPix(int a, int b, QString s)
{
    PixSizeH=b;
    PixSizeW=a;
    pix.load(s);
    pix=pix.scaled(PixSizeW,PixSizeH);
    core.setHeight(PixSizeH);
    core.setWidth(PixSizeW);
}
