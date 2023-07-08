#include "flyers.h"

Flyers::Flyers()
{
    X=0;
    Y=0;
    speed=0;
    PixSizeH=0;
    PixSizeW=0;
}

void Flyers::setPosition(int x, int y)
{
    X=x;
    Y=y;

}

void Flyers::setPix(int a, int b, QString s)
{
    PixSizeH=b;
    PixSizeW=a;
    pix.load(s);
    pix=pix.scaled(PixSizeW,PixSizeH);
}
