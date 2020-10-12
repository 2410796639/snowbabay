#include "widget.h"
#include <QPainter>
#include <QPushButton>
#include <QFont>
#include <QFile>
#include <QTextCodec>
#include <QtGlobal>
#include <QTime>
#include <QDebug>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //设置窗口大小
    resize(600,300);
    //设置窗口3个选项按钮
    QPushButton *p=new QPushButton [3];
    p[0].setText("开始游戏");
    p[1].setText("继续游戏");
    p[2].setText("退出游戏");
    //设置按钮属性
    for(int i=0;i<3;i++)
    {
        p[i].setGeometry(200,60+60*i,200,50);
        p[i].setFlat(true);
        p[i].setStyleSheet("font-size:20px");
        p[i].show();
        p[i].setParent(this);

    }
    //退出游戏
    connect((p+2),&QPushButton::clicked,this,&Widget::close);
    //开始游戏并跳转窗口
    connect(p,&QPushButton::clicked,this,&Widget::changewin);
    //设置继续游戏按钮
    connect((p+1),&QPushButton::clicked,
            [=]()
    {
        //判断是否有存档
        QFile judge_file("D:/QTcode/PIG/pig_information.txt");
            if(judge_file.exists()==true)
            {
                //读取存档信息
                judge_file.open(QIODevice::ReadOnly);
                QString ss=judge_file.readLine();
                int sumday;
                int blankcount=0;
                double money;
                int index=-1;
                int index0=-1;
                //读取运营天数与余额信息
                for(int i=0;i<ss.length();i++)
                {
                    if(ss[i]==' ')
                    {
                        index=index0;
                        index0=i;
                        QString str=ss.mid(index+1,index0-index-1);
                        blankcount++;
                        if(blankcount==1)
                        {
                            sumday=str.toInt();
                            str.clear();
                        }else if(blankcount==2)
                        {
                            money=str.toDouble();
                            str.clear();
                        }
                    }
                }
                w.sec=sumday;
                w.summoney=money;
                //读取每只猪的信息
                for(int i=0;i<100;i++)
                {
                    for(int j=0;j<10;j++)
                    {
                        blankcount=0;

                        w.pigcage[i].cagenumber=i;
                        int index1=-1,index2=-1;
                        QString ss=judge_file.readLine();
                        if(ss=='0')
                        {
                            w.pigcage[i].pigpen[j].blank=true;
                            w.pigcage[i].pigsum++;
                            continue;
                        }
                        else{
                            w.pigcage[i].pigpen[j].blank=false;
                        for(int k=0;k<ss.length();k++)
                        {

                            if(ss[k]==' ')
                            {
                                index1=index2;
                                index2=k;
                                QString str=ss.mid(index1+1,k-1-index1);
                                blankcount++;
                                if(blankcount==1)
                                {
                                    w.pigcage[i].pigpen[j].pigname=str;
                                    if(str=="黑猪")
                                    {
                                        w.pigcage[i].blacksum++;
                                        w.pigcage[i].blackpig=true;
                                    }else if(str=="白猪")
                                    {
                                        w.pigcage[i].whitesum++;
                                        w.pigcage[i].blackpig=false;

                                    }else if(str=="花猪")
                                    {
                                        w.pigcage[i].flowersum++;
                                        w.pigcage[i].blackpig=false;
                                    }
                                    str.clear();
                                }else if(blankcount==2)
                                {
                                    double tweight=str.toDouble();
                                    w.pigcage[i].pigpen[j].weight=tweight;
                                    str.clear();
                                }else if(blankcount==3)
                                {
                                    int tday=str.toInt();
                                    w.pigcage[i].pigpen[j].day=tday;
                                    str.clear();
                                }else if(blankcount==4)
                                {
                                    w.pigcage[i].pigpen[j].infec=str;
                                    str.clear();
                                }
                            }
                        }}


                    }
                }
                judge_file.close();
            }
            w.timerID=startTimer(100);
                this->hide();
                w.show();
    });
}

Widget::~Widget()
{

}
//设置主页面的背景图片
void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap(":/new/prefix1/image/background.jpg"));
}

void Widget::changewin()
{
    QFile judge_file("D:/QTcode/PIG/buy_sell.txt");
    if(judge_file.exists()==true)
            QFile::remove("D:/QTcode/PIG/buy_sell.txt");
    QFile judge_file1("D:/QTcode/PIG/buy_sell.txt");
    if(judge_file1.exists()==true)
            QFile::remove("D:/QTcode/PIG/pig_information.txt");
//    QFile file("D:/QTcode/PIG/buy_sell.txt");
//    OK=file.open(QIODevice::ReadWrite);
//    QFile file1("D:/QTcode/PIG/pig_information.txt");
//    OK=file1.open(QIODevice::ReadWrite);
    //初始化每个猪圈猪的数量，猪圈标号
        for(int i=0;i<100;i++)
        {
            w.sum+=w.pigcage[i].pigsum;
            w.pigcage[i].pigsum=6;
            w.pigcage[i].cagenumber=i;
        }
        //随机黑猪猪圈数
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        w.blackcage=qrand()%40;
        //白猪，花猪初始化
        for(int i=0;i<100-w.blackcage;i++)
        {
            //确定有无黑猪
            w.pigcage[i].blackpig=false;
            w.pigcage[i].infection=false;
            //随机白猪数量

            int white=qrand()%6;

            w.pigcage[i].whitesum=white;
            w.pigcage[i].flowersum=6-white;
            w.pigcage[i].blacksum=0;
            w.wsum+=w.pigcage[i].whitesum;
            w.fsum+=w.pigcage[i].flowersum;
            for(int j=0;j<6;j++)
            {
                w.pigcage[i].pigpen[j].blank=false;

                w.pigcage[i].pigpen[j].weight=20+(double)(qrand()%300)/10;
                w.pigcage[i].pigpen[j].infection=false;
                if(w.pigcage[i].pigpen[j].infection==false)
                {
                    w.pigcage[i].pigpen[j].infec="否";
                }else
                {
                    w.pigcage[i].pigpen[j].infec="是";
                }
                if(j<white)
                {
                    w.pigcage[i].pigpen[j].pigname="白猪";

                }else
                {
                    w.pigcage[i].pigpen[j].pigname="花猪";
                }
            }
        }
        //黑猪类似
        for(int i=100-w.blackcage;i<100;i++)
        {
            w.pigcage[i].whitesum=0;
            w.pigcage[i].flowersum=0;
            w.pigcage[i].blacksum=6;
            w.pigcage[i].blackpig=true;
            w.pigcage[i].infection=false;

            w.bsum+=w.pigcage[i].blacksum;
            for(int j=0;j<6;j++)
            {
                w.pigcage[i].pigpen[j].blank=false;

                w.pigcage[i].pigpen[j].weight=20+(double)(qrand()%300)/10;
                w.pigcage[i].pigpen[j].pigname="黑猪";
                w.pigcage[i].pigpen[j].infection=false;
                //qDebug()<<w.pigcage[i].pigpen[j].pigname;
            }
        }

       qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        int a=qrand()%100;
        int b=qrand()%6;
        w.pigcage[a].pigpen[b].infection=true;
        w.pigcage[a].pigpen[b].infec="是";
        w.pigcage[a].infection=true;
        qDebug()<<a<<b;
    this->hide();

    w.show();
}
