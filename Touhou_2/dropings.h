#ifndef DROPINGS_H
#define DROPINGS_H

#include"flyers.h"
class Dropings:public Flyers
{
public:
    Dropings();
    bool free;
    QRect core;
    QString p;
    void updatePosition();
    void setPix(int a,int b,QString s);
};

#endif // DROPINGS_H
