#ifndef FLYERS_H
#define FLYERS_H

#include<QPixmap>

//飞行物体抽象类
class Flyers
{
public:
    Flyers();
    int X;
    int Y;//位置坐标
    int speed;//速度
    QPixmap pix;//图片
    int PixSizeW;
    int PixSizeH;
    void setPosition(int x, int y);//设置位置
    void setPix(int a,int b,QString s);
};

#endif // FLYERS_H
