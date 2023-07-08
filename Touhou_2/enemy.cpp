#include "enemy.h"

Enemy::Enemy()
{
    X=0;
    Y=0;
    speed=5;
    bulletnumber=1;
    shootRecord=0;
    shootInterval=20;
    PixSizeH=120;
    PixSizeW=120;
    pix.load(":/res/enemy_01_01.png");
    pix=pix.scaled(PixSizeW,PixSizeH);
    core.setHeight(PixSizeH);
    core.setWidth(PixSizeW);
    core.moveTo(X,Y);
    free=true;
    life=100;
    powernum=3;
    fairypix[0]=":/res/enemy_01_01.png";
    fairypix[1]=":/res/enemy_01_02.png";
    fairypix[2]=":/res/enemy_01_03.png";
    fairypix[3]=":/res/enemy_01_04.png";
    fairypix[4]=":/res/enemy_01_05.png";
    fairypix[5]=":/res/enemy_01_06.png";
}

void Enemy::updatePosition()
{
    if(free==true){
        return;
    }
    else{
        Y+=speed;
        core.moveTo(X,Y);
        shoot();
        if(Y>=1200){
            free=true;
        }
    }
}

void Enemy::updateChildPosition()
{
    for(int j=0;j<bulletnumber;j++)
    {
        if(bullet[j].free==false)
            bullet[j].updatePosition();
    }
}

void Enemy::shoot()
{
    shootRecord++;
    if(shootRecord < shootInterval)
    {
        return;
    }
    shootRecord = 0;
    for(int i=0;i<bulletnumber;i++){
        if(bullet[i].free==true){
            bullet[i].free=false;
            bullet[i].X=X+PixSizeW*0.5-bullet[i].PixSizeW*0.5;
            bullet[i].Y=Y+PixSizeH*0.5-bullet[i].PixSizeH*0.5;
            break;
        }
    }
}

void Enemy::droppowerpoint(Dropings &p)
{
    int x=X+PixSizeW-p.PixSizeW;
    int y=Y+PixSizeH-p.PixSizeH;
    int a=rand()%(x-X)+X;
    int b=rand()%(y-Y)+Y;
    p.free=false;
    p.X=a;
    p.Y=b;
}

void Enemy::hit(PlayerBullet b[],int n)
{
    for(int j=0;j<n;j++)
    {
        if(b[j].free==true)
            continue;
        else
        {
            if(core.intersects(b[j].core))
            {
                life-=b[j].atk;
                b[j].free=true;
            }
        }
    }
}
