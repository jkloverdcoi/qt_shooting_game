#include "dropings.h"

Dropings::Dropings()
{
    X=0;
    Y=0;
    speed=5;
    PixSizeH=50;
    PixSizeW=50;
    free=true;
    core.setWidth(PixSizeW);
    core.setHeight(PixSizeH);
    core.moveTo(X,Y);
    p=":/res/powerpoint.png";
    pix.load(p);
    pix=pix.scaled(PixSizeW,PixSizeH);
}

void Dropings::updatePosition()
{
    if(free==true){
        return;
    }
    else{
        Y+=speed;
        core.moveTo(X,Y);
        if(Y>=1200){
            free=true;
        }
    }
}

void Dropings::setPix(int a, int b, QString s)
{
    PixSizeH=b;
    PixSizeW=a;
    core.setWidth(PixSizeW);
    core.setHeight(PixSizeH);
    pix.load(s);
    pix=pix.scaled(PixSizeW,PixSizeH);
}
