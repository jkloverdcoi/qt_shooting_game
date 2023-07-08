#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Qpainter>
#include"menubutton.h"
#include<QDebug>
#include<QTimer>
#include "gamescene.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*页面基本设置*/
    setFixedSize(1600,1200);
    move(150,0);
    setWindowIcon(QIcon(":/res/icon.ico"));
    setWindowTitle("东方弹幕纪行");
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });
    music.setInterval(232000);
    player->setMedia(QUrl::fromLocalFile("D:\\QtPrograms\\Touhou_2\\res\\menubgm.mp3"));//“:/res/”不能正常播放，原因未知
    player->setVolume(50); //0~100音量范围,默认是100
    clicksound->setMedia(QUrl::fromLocalFile("D:\\QtPrograms\\Touhou_2\\res\\clickbutton.mp3"));
    clicksound->setVolume(100);
    playmusic();
    thishide=false;
    /*界面按钮设置*/
//    Menubutton* optionBtn=new Menubutton(":/res/Option.png",90,700);
    Menubutton* startBtn=new Menubutton(":/res/gamestart.png",90,600);
    Menubutton* quitBtn=new Menubutton(":/res/quitbutton.png",90,700);


//    optionBtn->setParent(this);
//    optionBtn->setToolTip("设置");
//    optionBtn->setToolTipDuration(5000);
//    connect(optionBtn,&Menubutton::clicked,[=](){
//        clicksound->play();
//        optionBtn->hide();
//        startBtn->hide();
//        quitBtn->hide();
//    });
    startBtn->setParent(this);
    startBtn->setToolTip("开始游戏");
    startBtn->setToolTipDuration(5000);
    connect(startBtn,&Menubutton::clicked,[=](){
        s=new GameScene;
        clicksound->play();
        for(int i=0;i<4;i++){
            QTimer::singleShot(250*i,this,[=](){
                startBtn->flash();
            });
        }//图标闪烁
        QTimer::singleShot(1000,this,[=](){
            player->stop();
            thishide=true;
            this->hide();
            s->initialize();
            s->show();
        });
        connect(s->over,&GameOverScene::backtomenu,[=](){
            thishide=false;
            playmusic();
            this->show();
        });
    });
    quitBtn->setParent(this);
    quitBtn->setToolTip("退出游戏");
    quitBtn->setToolTipDuration(5000);
    connect(quitBtn,&Menubutton::clicked,[=](){
        clicksound->play();
        this->close();
    });
}
/*页面绘制*/
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/Background_01.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*2,pix.height()*2);
    painter.drawPixmap(100,150,pix);
}

void MainWindow::playmusic()
{
    music.start();
    player->play();
    connect(&music,&QTimer::timeout,[=](){
        if(thishide==true)
        {
            return;
        }
        else{
            player->stop();
            player->play();
        }
    });
}
MainWindow::~MainWindow()
{
    delete ui;
}
