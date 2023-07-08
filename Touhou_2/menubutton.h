#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include<QPushButton>

class Menubutton : public QPushButton
{
    Q_OBJECT
public:
    Menubutton(QString normalImg,int a,int b);
    QString normalImg;
    void enterEvent(QEvent *event);//右移动画
    void leaveEvent(QEvent *event);//左移动画
    void flash();//闪烁动画
    int X;//坐标
    int Y;
signals:

public slots:
};

#endif // MENUBUTTON_H
