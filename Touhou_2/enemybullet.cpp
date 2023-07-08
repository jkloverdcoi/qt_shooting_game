#include "enemybullet.h"

EnemyBullet::EnemyBullet()
{
    X=0;
    Y=0;
    speed=5;
    PixSizeH=50;
    PixSizeW=50;
    pix.load(":/res/b01.png");
    pix=pix.scaled(PixSizeW,PixSizeH);
    core.setHeight(30);
    core.setWidth(30);
    core.moveTo(X+PixSizeW*0.5-core.width()*0.5,Y+PixSizeH*0.5-core.height()*0.5);
    free=true;
    shootangle=45;
    type1pix[0]=":/res/b01.png";
    type1pix[1]=":/res/b02.png";
    type1pix[2]=":/res/b03.png";
    type1pix[3]=":/res/b04.png";
    type1pix[4]=":/res/b05.png";
    type1pix[5]=":/res/b06.png";
    type1pix[6]=":/res/b07.png";
    type1pix[7]=":/res/b08.png";
    type2pix[0]=":/res/c01.png";
    type2pix[1]=":/res/c02.png";
    type2pix[2]=":/res/c03.png";
    type2pix[3]=":/res/c04.png";
    type2pix[4]=":/res/c05.png";
    type2pix[5]=":/res/c06.png";
    type2pix[6]=":/res/c07.png";
    type2pix[7]=":/res/c08.png";
    type2pix[8]=":/res/c09.png";
}

void EnemyBullet::updatePosition()
{
    if(free==true){
        return;
    }
    else{
        Y+=speed*sin(shootangle*PI/180);
        X+=speed*cos(shootangle*PI/180);
        core.moveTo(X+PixSizeW*0.5-core.width()*0.5,Y+PixSizeH*0.5-core.height()*0.5);
        if(Y>=1200){
            free=true;
        }
    }
}

void EnemyBullet::setPix(int an,int s, int pw, int ph, int a, int b, QString str)
{
    shootangle=an;
    speed=s;
    PixSizeH=ph;
    PixSizeW=pw;
    pix.load(str);
    pix=pix.scaled(PixSizeW,PixSizeH);
    core.setHeight(b);
    core.setWidth(a);
    core.moveTo(X+PixSizeW*0.5-core.width()*0.5,Y+PixSizeH*0.5-core.height()*0.5);
    free=true;
}
