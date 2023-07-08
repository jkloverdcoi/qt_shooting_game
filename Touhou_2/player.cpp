#include "player.h"

Player::Player()
{
     PixSizeW=100;
     PixSizeH=180;
     speed=10;
     X=1600/2-PixSizeW/2;
     Y=900;
     shootRecord=0;
     shootInterval=10;
     pix.load(":/res/player.png");
     pix=pix.scaled(PixSizeW,PixSizeH);
     pixs.load(":/res/player_02.png");
     pixs=pixs.scaled(PixSizeW,PixSizeH);
     core.setHeight(45);
     core.setWidth(45);
     corePix.load(":/res/core.png");
     corePix=corePix.scaled(45,45);
     core.moveTo(X+PixSizeW/2-core.width()/2,Y+PixSizeH/2-core.height()/2);
     life=3;
     bomb=4;
     power=1.0;
     safe=false;
     for(int i=0;i<4;i++)
     {
         Wingman[i].setPix(85,85,":/res/shootedobject.png");
     }
     for(int i=0;i<30;i++)
     {
         type2Left[i].setPix(60,80,":/res/playerbullet_01.png");
         type2Right[i].setPix(60,80,":/res/playerbullet_01.png");
         type3Left[i].setPix(60,80,":/res/playerbullet_02.png");
         type3Right[i].setPix(60,80,":/res/playerbullet_02.png");
     }
}

void Player::updateBulletPos(PlayerBullet b[])
{
    for(int i=0;i<30;i++)
    {
        if(b[i].free==false)
        {
            b[i].updatePosition();
        }
    }
}

void Player::setPosition()
{
    core.moveTo(X+PixSizeW/2-core.width()/2,Y+PixSizeH/2-core.height()/2);
    updateBulletPos(type1Left);
    updateBulletPos(type1Right);
    if(power>=2.0)
    {
        updateBulletPos(type2Left);
        updateBulletPos(type2Right);
        Wingman[0].X=X-110;
        Wingman[0].Y=Y-Wingman[0].PixSizeH;
        Wingman[1].X=X+110+PixSizeW-Wingman[1].PixSizeW;
        Wingman[1].Y=Y-Wingman[1].PixSizeH;
    }
    if(power>=4.0)
    {
        updateBulletPos(type3Left);
        updateBulletPos(type3Right);
        Wingman[2].X=Wingman[0].X-150;
        Wingman[2].Y=Y-Wingman[2].PixSizeH+PixSizeH;
        Wingman[3].X=Wingman[1].X+150;
        Wingman[3].Y=Y-Wingman[3].PixSizeH+PixSizeH;
    }
}

void Player::shoot()
{
    //累加时间间隔记录变量
    shootRecord++;
    //判断如果记录数字，未达到发射间隔，直接return
    if(shootRecord < shootInterval)
    {
        return;
    }
    //到达发射时间处理
    //重置发射时间间隔记录
    shootRecord = 0;
    for(int i=0;i<30;i++)
    {
        if(type1Left[i].free==true)
        {
            type1Left[i].free=false;
            type1Right[i].atk=20+power*power;
            type1Left[i].X=X;
            type1Left[i].Y=Y-type1Left[i].PixSizeH;
            break;
        }
    }
    for(int i=0;i<30;i++)
    {
        if(type1Right[i].free==true)
        {
            type1Right[i].free=false;
            type1Right[i].atk=20+power*power;
            type1Right[i].X=X+PixSizeW-type1Right[i].PixSizeW;
            type1Right[i].Y=Y-type1Right[i].PixSizeH;
            break;
        }
    }
    if(power>=2.0)
    {
        shootbullet(type2Left,0);
        shootbullet(type2Right,1);
    }
    if(power>=4.0)
    {
        shootbullet(type3Left,2);
        shootbullet(type3Right,3);
    }
}

void Player::shootbullet(PlayerBullet b[],int x)
{
    for(int i=0;i<30;i++)
    {
        if(b[i].free==true)
        {
            b[i].free=false;
            b[i].atk=20+power*power;
            b[i].X=Wingman[x].X+Wingman[x].PixSizeW*0.5-b[i].PixSizeW*0.5;
            b[i].Y=Wingman[x].Y-b[i].PixSizeH;
            break;
        }
    }
}

void Player::hit()
{
    X=1600/2-PixSizeW/2;
    Y=900;
    life--;
    bomb=4;
    if(power>=2.0)
        power-=1.0;
    else
        power=1.0;
}
