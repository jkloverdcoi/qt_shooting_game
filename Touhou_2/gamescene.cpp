#include "gamescene.h"

GameScene::GameScene(QWidget *parent) : QWidget(parent)
{
    over=new GameOverScene;
    //判定游戏结束
    connect(this,&GameScene::Gameclear,[=]{
        over->win=true;
        over->update();
        over->showscore(score);
        bgm->stop();
        over->playbgm();
        delete this;
        over->show();
    });
    connect(this,&GameScene::Gameover,[=]()
    {
        over->win=false;
        over->update();
        over->showscore(score);
        over->playbgm();
        bgm->stop();
        delete this;
        over->show();
    });
    //无敌状态持续三秒
    connect(this,&GameScene::playersafe,[=]()
    {
        player.safe=true;
        QTimer::singleShot(3000,this,[=]()
        {
            player.safe=false;
        });
    });
    //bomb
    connect(this,&GameScene::shootbomb,[=]()
    {
        bomb=true;
        player.bomb--;
        for(int i=0;i<fairyNumber;i++)
        {
            if(fairy[i].free==false)
                fairy[i].life=0;
            for(int j=0;j<fairy[i].bulletnumber;j++)
            {
                if(fairy[i].bullet[j].free==false)
                    fairy[i].bullet[j].free=true;
            }
        }
        QTimer::singleShot(3000,this,[=]()
        {
            bomb=false;
        });
    });
}

void GameScene::initialize()
{
    Width=1600,Hidth=1200;
    setFixedSize(Width,Hidth);
    move(150,0);
    setWindowIcon(QIcon(":/res/icon.ico"));
    setWindowTitle("东方弹幕纪行");
    powerinfor=new QLabel;
    timeinfor=new QLabel;
    up=false;
    down=false;
    left=false;
    right=false;
    z=false;
    shift=false;
    bomb=false;
    for(int i=0;i<10;i++)
        bonus1[i]=false;
    for(int i=0;i<5;i++)
        bonus2[i]=false;
    tempspeed=player.speed;
    timer.setInterval(10);
    clock=180;
    rank=0;
    sec.setInterval(1000);
    halfmin.setInterval(30000);
    musictimer.setInterval(142000);
    bgm->setMedia(QUrl::fromLocalFile("D:\\QtPrograms\\Touhou_2\\res\\gamescenebgm.mp3"));
    bgm->setVolume(50);
    enemydefeatsound->setMedia(QUrl::fromLocalFile("D:\\QtPrograms\\Touhou_2\\res\\enemydefeat.mp3"));
    enemydefeatsound->setVolume(100);
    hitsound->setMedia(QUrl::fromLocalFile("D:\\QtPrograms\\Touhou_2\\res\\hit.mp3"));
    hitsound->setVolume(100);
    bombsound->setMedia(QUrl::fromLocalFile("D:\\QtPrograms\\Touhou_2\\res\\bomb.mp3"));
    bombsound->setVolume(100);
    bonusound->setMedia(QUrl::fromLocalFile("D:\\QtPrograms\\Touhou_2\\res\\bonus.mp3"));
    bonusound->setVolume(100);
    getpointsound->setMedia(QUrl::fromLocalFile("D:\\QtPrograms\\Touhou_2\\res\\getpoint.mp3"));
    getpointsound->setVolume(100);
    srand((unsigned int)time(NULL));//随机数种子
    fairyNumber=50;
    score=0;
    for(int i=0;i<200;i++)
    {
        scorepoint[i].setPix(50,50,":/res/score.png");
        scorepoint[i].free=true;
    }
    for(int i=0;i<fairyNumber;i++)
    {
        fairy[i].speed=rand()%(10-5)+5;
        int a=rand()%6;
        fairy[i].pix.load(fairy[i].fairypix[a]);
        fairy[i].pix=fairy[i].pix.scaled(fairy[i].PixSizeW,fairy[i].PixSizeH);
        for(int j=0;j<10;j++)
        {
            int b=rand()%8;
            int a=rand()%9;
            int an=rand()%180;
            int s=rand()%(10-5)+5;
            int ty=rand()%2;
            if(ty==0)
                fairy[i].bullet[j].setPix(an,s,100,100,75,75,fairy[i].bullet[j].type1pix[b]);
            else
                fairy[i].bullet[j].setPix(an,s,50,50,35,35,fairy[i].bullet[j].type2pix[a]);
        }
    }//随机设定敌机参数
    EnemyShowRecord=0;
    EnemyShowInterval=30;
    GameStart();
}

void GameScene::GameStart()
{
    timer.start();
    sec.start();
    halfmin.start();
    playbgm();
    connect(&timer,&QTimer::timeout,[=]
    {
        showEnemy();
        updatePosition();
        update();
        updateInformation();
        checkCollision();
        checklife();
        bonusjudge();
    });
    connect(&sec,&QTimer::timeout,[=]{
        clock--;
        if(clock==0)
        {
            emit Gameclear();
        }
    });
    connect(&halfmin,&QTimer::timeout,[=]{
        rank++;
        updateRank();
    });
}

void GameScene::updatePosition()
{
    //玩家坐标计算
    if(shift==true)
        player.speed=tempspeed/2;
    else
        player.speed=tempspeed;
    //判断慢速模式
    if(up==true)
    {
        if(player.Y-player.speed<=0)
            player.Y=0;
        else
            player.Y-=player.speed;
    }
    if(down==true)
    {
        if(player.Y+player.PixSizeH+player.speed>=Hidth)
            player.Y=Hidth-player.PixSizeH;
        else
            player.Y+=player.speed;
    }
    if(left==true)
    {
        if(player.X-player.speed<=0)
            player.X=0;
        else
            player.X-=player.speed;
    }
    if(right==true)
    {
        if(player.X+player.PixSizeW+player.speed>=Width)
            player.X=Width-player.PixSizeW;
        else
            player.X+=player.speed;
    }
    player.setPosition();
    //玩家射击判断
    if(z==true)
        player.shoot();
    //敌机及子弹坐标计算
    for(int i=0;i<fairyNumber;i++)
    {
        fairy[i].updatePosition();
        fairy[i].updateChildPosition();
    }
    for(int i=0;i<100;i++)
    {
        if(powerpoint[i].free==false)
        {
            powerpoint[i].updatePosition();
        }
    }
    for(int i=0;i<200;i++)
    {
        if(scorepoint[i].free==false)
        {
            scorepoint[i].updatePosition();
        }
    }
}

void GameScene::updateInformation()
{
    powerinfor->setParent(this);
    powerinfor->move(10,10);
    powerinfor->setFixedSize(500,100);
    powerinfor->setText("Power:"+QString::number(player.power)+"/5.0"+"\n"+"Score:"+QString::number(score));
    timeinfor->setParent(this);
    timeinfor->move(1200,0);
    timeinfor->setFixedSize(500,200);
    timeinfor->setText("Time:"+QString::number(clock));
    QFont ft;
    ft.setPointSize(20);
    ft.setFamily("黑体");
    ft.setBold(true);
    powerinfor->setFont(ft);
    powerinfor->show();
    timeinfor->setFont(ft);
    timeinfor->show();
}

void GameScene::updateRank()
{
    EnemyShowInterval=30-rank;
    for(int i=0;i<fairyNumber;i++)
    {
        fairy[i].bulletnumber=1+rank;
        fairy[i].life=100+rank*10;
        for(int j=0;j<10;j++)
        {
            int x=10+rank;
            int s=rand()%(x-5)+5;
            fairy[i].bullet[j].speed=s;

       }
    }
}

void GameScene::bonusjudge()
{
    for(int i=0;i<10;i++)
    {
        if(score>=5000*(i+1)&&bonus1[i]==false)
        {
            player.bomb++;
            bonusound->play();
            bonus1[i]=true;
        }
    }
    for(int j=0;j<5;j++)
    {
        if(score>=10000*(j+1)&&bonus2[j]==false)
        {
            player.life++;
            bonusound->play();
            bonus2[j]=true;
        }
    }
}

void GameScene::paintEvent(QPaintEvent *event)
{
     QPainter painter(this);
     painter.drawPixmap(0,0,this->width(),this->height(),background.map);//绘制背景
     QPixmap pix;
     pix.load(":/res/life.png");
     pix=pix.scaled(70,70);
     for(int i=0;i<player.life;i++)
     {
         painter.drawPixmap(i*pix.width(),Hidth-pix.height(),pix);
     }//绘制血量
     pix.load(":/res/bomb.png");
     pix=pix.scaled(70,70);
     for(int i=0;i<player.bomb;i++)
     {
         painter.drawPixmap(i*pix.width(),Hidth-70-pix.height(),pix);
     }//绘制bomb
     if(player.safe==true)
         painter.drawPixmap(player.X,player.Y,player.pixs);
     else
         painter.drawPixmap(player.X,player.Y,player.pix);//绘制角色
     //绘制判定点
     if(shift==true)
         painter.drawPixmap(player.core,player.corePix);
     //绘制玩家子弹和僚机
     for(int i=0;i<30;i++)
     {
         if(player.type1Left[i].free==false)
         {
             painter.drawPixmap(player.type1Left[i].X,player.type1Left[i].Y,player.type1Left[i].pix);
         }
     }
     for(int i=0;i<30;i++)
     {
         if(player.type1Right[i].free==false)
         {
             painter.drawPixmap(player.type1Right[i].X,player.type1Right[i].Y,player.type1Right[i].pix);
         }
     }
     if(player.power>=2.0)
     {
         painter.drawPixmap(player.Wingman[0].X,player.Wingman[0].Y,player.Wingman[0].pix);
         painter.drawPixmap(player.Wingman[1].X,player.Wingman[1].Y,player.Wingman[1].pix);
         for(int i=0;i<30;i++)
         {
             if(player.type2Left[i].free==false)
             {
                 painter.drawPixmap(player.type2Left[i].X,player.type2Left[i].Y,player.type2Left[i].pix);
             }
         }
         for(int i=0;i<30;i++)
         {
             if(player.type2Right[i].free==false)
             {
                 painter.drawPixmap(player.type2Right[i].X,player.type2Right[i].Y,player.type2Right[i].pix);
             }
         }
     }
     if(player.power>=4.0)
     {
         painter.drawPixmap(player.Wingman[2].X,player.Wingman[2].Y,player.Wingman[2].pix);
         painter.drawPixmap(player.Wingman[3].X,player.Wingman[3].Y,player.Wingman[3].pix);
         for(int i=0;i<30;i++)
         {
             if(player.type3Left[i].free==false)
             {
                 painter.drawPixmap(player.type3Left[i].X,player.type3Left[i].Y,player.type3Left[i].pix);
             }
         }
         for(int i=0;i<30;i++)
         {
             if(player.type3Right[i].free==false)
             {
                 painter.drawPixmap(player.type3Right[i].X,player.type3Right[i].Y,player.type3Right[i].pix);
             }
         }
     }
     for(int t=0;t<100;t++)
     {
         if(powerpoint[t].free==false)
         {
             painter.drawPixmap(powerpoint[t].X,powerpoint[t].Y,powerpoint[t].pix);
         }
     }//绘制P点
     for(int t=0;t<200;t++)
     {
         if(scorepoint[t].free==false)
         {
             painter.drawPixmap(scorepoint[t].X,scorepoint[t].Y,scorepoint[t].pix);
         }
     }//绘制蓝点
     //绘制敌机
     for(int i=0;i<fairyNumber;i++)
     {
         if(fairy[i].free==false)
         {
             painter.drawPixmap(fairy[i].X,fairy[i].Y,fairy[i].pix);
         }
         for(int j=0;j<fairy[i].bulletnumber;j++)
         {
             if(fairy[i].bullet[j].free==false)
             {
                 painter.drawPixmap(fairy[i].bullet[j].X,fairy[i].bullet[j].Y,fairy[i].bullet[j].pix);
             }//绘制敌机子弹
         }
     }
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Left)
        left=true;
    if(event->key()==Qt::Key_Right)
        right=true;
    if(event->key()==Qt::Key_Up)
        up=true;
    if(event->key()==Qt::Key_Down)
        down=true;
    if(event->key()==Qt::Key_Z)
        z=true;
    if(event->key()==Qt::Key_Shift)
        shift=true;
    if(event->key()==Qt::Key_X)
    {
        if(bomb==false&&player.bomb>0)
        {
            emit shootbomb();
            bombsound->play();
            emit playersafe();
        }
        else
            event->ignore();
    }
}

void GameScene::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Left)
        left=false;
    if(event->key()==Qt::Key_Right)
        right=false;
    if(event->key()==Qt::Key_Up)
        up=false;
    if(event->key()==Qt::Key_Down)
        down=false;
    if(event->key()==Qt::Key_Z)
        z=false;
    if(event->key()==Qt::Key_Shift)
        shift=false;
}

void GameScene::showEnemy()
{
    EnemyShowRecord++;
    if(EnemyShowRecord<EnemyShowInterval)
    {
        return;
    }
    EnemyShowRecord=0;
    for(int i=fairyNumber-1;i>=0;i--)
    {
        if(fairy[i].free==true)
        {
            fairy[i].life=100;
            fairy[i].free=false;
            fairy[i].life=100;
            fairy[i].X=rand()%(Width-fairy[i].PixSizeW);
            fairy[i].Y=-fairy[i].PixSizeH;
            break;
        }
    }
}

void GameScene::checkCollision()
{
    for(int i=0;i<fairyNumber;i++)
    {
        //敌机子弹与自机
        for(int j=0;j<fairy[i].bulletnumber;j++)
        {
            if(fairy[i].bullet[j].free==false)
            {
                if(fairy[i].bullet[j].core.intersects(player.core))
                {
                    fairy[i].bullet[j].free=true;
                    if(player.safe==false)
                    {
                        emit playersafe();
                        hitsound->play();
                        player.hit();
                    }
                }
            }
        }
        if(fairy[i].free==true)
        {
            continue;
        }
        //敌机与自机子弹
        fairy[i].hit(player.type1Left,30);
        fairy[i].hit(player.type1Right,30);
        fairy[i].hit(player.type2Left,30);
        fairy[i].hit(player.type2Right,30);
        fairy[i].hit(player.type3Left,30);
        fairy[i].hit(player.type3Right,30);
        //敌机与自机
        if(fairy[i].core.intersects(player.core))
        {
            if(player.safe==false)
            {
                emit playersafe();
                hitsound->play();
                player.hit();
            }
        }
    }
    //自机与P点
    for(int t=0;t<100;t++)
    {
        if(powerpoint[t].free==false)
        {
            if(powerpoint[t].core.intersects(player.core))
            {
                powerpoint[t].free=true;
                getpointsound->play();
                if(player.power<=4.95){
                    player.power+=0.05;
                }
                else
                    player.power=5.0;
            }
        }
    }
    for(int t=0;t<200;t++)
    {
        if(scorepoint[t].free==false)
        {
            if(scorepoint[t].core.intersects(player.core))
            {
                getpointsound->play();
                scorepoint[t].free=true;
                score+=100;
            }
        }
    }
}

void GameScene::checklife()
{
    //检测敌机血量
    for(int i=0;i<fairyNumber;i++)
    {
        if(fairy[i].free==true)
            continue;
        else
        {
            if(fairy[i].life<=0)
            {
                score+=10+abs(fairy[i].Y/10);
                enemydefeatsound->play();
                int j=0;
                for(int t=0;t<100;t++)
                {
                    if(powerpoint[t].free==false)
                        continue;
                    else
                    {
                        if(player.power<=4.95)
                        {
                            fairy[i].droppowerpoint(powerpoint[t]);
                        }
                        j++;
                        if(j==3)
                            break;
                    }
                }
                int n=0;
                if(player.power==5.0){
                    for(int t=0;t<200;t++)
                    {
                        if(scorepoint[t].free==false)
                            continue;
                        else
                        {
                            fairy[i].droppowerpoint(scorepoint[t]);
                            n++;
                        }
                        if(n==3)
                            break;
                    }
                }
                fairy[i].free=true;
            }
        }
    }
    //检测自机血量
    if(player.life<0)
    {
        emit Gameover();
    }
}

void GameScene::playbgm()
{
    musictimer.start();
    bgm->play();
    connect(&musictimer,&QTimer::timeout,[=](){
        bgm->stop();
        bgm->play();
    });
}
