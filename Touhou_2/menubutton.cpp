#include "menubutton.h"
#include<QPushButton>
#include<QDebug>
#include<QPropertyAnimation>
#include<QTimer>
Menubutton::Menubutton(QString normalImg,int a,int b)
{
    X=a;
    Y=b;//固定按钮初始位置
    this->move(X,Y);
    QPixmap pix;
    bool ret=pix.load(normalImg);
    if(!ret)
    {
        qDebug()<<"图片加载失败";
        return;
    }
    pix=pix.scaled(pix.width()*2.5,pix.height()*2.5);
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
}
void Menubutton::enterEvent(QEvent *event)
{
    QPropertyAnimation * an = new QPropertyAnimation(this,"geometry");
    an->setDuration(1500);
    an->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    an->setEndValue(QRect(this->X+30,this->Y,this->width(),this->height()));
    an->setEasingCurve(QEasingCurve::Linear);
    an->start();

}
void Menubutton::leaveEvent(QEvent *event)
{
    QPropertyAnimation * an = new QPropertyAnimation(this,"geometry");
    an->setDuration(1500);
    an->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    an->setEndValue(QRect(this->X-30,this->Y,this->width(),this->height()));
    an->setEasingCurve(QEasingCurve::Linear);
    an->start();
}
void Menubutton::flash(){
    this->hide();
    QTimer::singleShot(125,this,[=](){
        this->show();
    });
}
