#include "gameoverscene.h"

GameOverScene::GameOverScene(QWidget *parent) : QWidget(parent)
{
    setFixedSize(2700,1865);
    move(150,0);
    setWindowIcon(QIcon(":/res/icon.ico"));
    setWindowTitle("东方弹幕纪行");
    QPixmap pix;
    pix.load(":/res/backtothemenu.png");
    pix=pix.scaled(pix.width()*1.5,pix.height()*1.5);
    back=new QPushButton;
    back->setFixedSize(pix.width(),pix.height());
    back->setStyleSheet("QPushButton{border:0px}");
    back->setIcon(pix);
    back->setIconSize(QSize(pix.width(),pix.height()));
    back->setParent(this);
    back->move(10,1600);
    connect(back,&QPushButton::clicked,[=](){
        clicksound->play();
        emit backtomenu();
        if(win==true)
            gameclearbgm->stop();
        else
            gameoverbgm->stop();
        delete this;
    });
    quit=new QPushButton;
    pix.load(":/res/quitgame.png");
    pix=pix.scaled(pix.width()*1.5,pix.height()*1.5);
    quit->setFixedSize(pix.width(),pix.height());
    quit->setStyleSheet("QPushButton{border:0px}");
    quit->setIcon(pix);
    quit->setIconSize(QSize(pix.width(),pix.height()));
    quit->setParent(this);
    quit->move(2700-pix.width(),1600);
    connect(quit,&QPushButton::clicked,[=](){
        clicksound->play();
        if(win==true)
            gameclearbgm->stop();
        else
            gameoverbgm->stop();
        this->close();
    });
    musictimerwin.setInterval(97000);
    gameclearbgm->setMedia(QUrl::fromLocalFile("D:\\QtPrograms\\Touhou_2\\res\\gameclearbgm.mp3"));
    gameclearbgm->setVolume(50);
    musictimerlose.setInterval(126000);
    gameoverbgm->setMedia(QUrl::fromLocalFile("D:\\QtPrograms\\Touhou_2\\res\\gameoverbgm.mp3"));
    gameoverbgm->setVolume(50);
    clicksound->setMedia(QUrl::fromLocalFile("D:\\QtPrograms\\Touhou_2\\res\\clickbutton.mp3"));
    clicksound->setVolume(100);
}

void GameOverScene::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    QPixmap pix;
    if(win==false)
    {
        pix.load(":/res/background_02.png");
        painter.drawPixmap(0,0,this->width(),this->height(),pix);
        pix.load(":/res/Gameover.png");
        painter.drawPixmap(this->width()/2-pix.width()/2,this->height()/2-pix.height()/2,pix);
    }
    else
    {
        pix.load(":/res/background_temp.png");
        painter.drawPixmap(0,0,this->width(),this->height(),pix);
        pix.load(":/res/gameclear.png");
        painter.drawPixmap(this->width()/2-pix.width()/2,this->height()/2-pix.height()/2,pix);
    }
}

void GameOverScene::showscore(int a)
{
    infor=new QLabel;
    infor->setParent(this);
    infor->setFixedSize(1500,500);
    infor->move(this->width()/2-infor->width()/2,1200);
    infor->setText("您的分数："+QString::number(a));
    QFont ft;
    ft.setPointSize(50);
    ft.setFamily("黑体");
    ft.setBold(true);
    infor->setFont(ft);
}

void GameOverScene::playbgm()
{
    if(win==true)
    {
        musictimerwin.start();
        gameclearbgm->play();
        connect(&musictimerwin,&QTimer::timeout,[=](){
            gameclearbgm->stop();
            gameclearbgm->play();
        });
    }
    else
    {
        musictimerlose.start();
        gameoverbgm->play();
        connect(&musictimerlose,&QTimer::timeout,[=](){
            gameoverbgm->stop();
            gameoverbgm->play();
        });
    }
}

