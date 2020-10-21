#include "subwidget.h"
#include "ui_subwidget.h"
#include <QPainter>
#include <QPushButton>
#include <QWidget>
#include <QStackedWidget>
#include <QGridLayout>
#include <QScrollArea>
#include <QLabel>
#include <QMessageBox>
#include <QString>
#include <QtGlobal>
#include <QTime>
#include <QDebug>
#include <algorithm>
#include <QFile>
#include <QTextCodec>
#include <QCloseEvent>
#include <QFileInfo>
#include <QSound>
#include <QMediaPlayer>

subwidget::subwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::subwidget)
{
    ui->setupUi(this);
    //确定窗口大小
    resize(800,600);
    //开始时间按钮
    connect(ui->pushButton,&QPushButton::clicked,
            [=]()
    {
        timerID= this->startTimer(1000);
    });
    //停止时间按钮
    connect(ui->pushButton_2,&QPushButton::clicked,
            [=]()
    {
        this->killTimer(this->timerID);
    });

    //建立猪圈按钮
    QPushButton *btn=new QPushButton [100];
    int count =0;
    for(int i=0;i<100;i++)
    {
        btn[i].setParent(ui->widget_2);
        btn[i].resize(30,30);
        btn[i].move(50+i%5*50,50+count*30);
        btn[i].setStyleSheet("border-image:url(:/new/prefix1/image/timg (3).jpg)");
        btn[i].setText(QString("%1").arg(i));
        if(i%5==4)
        {
            count++;
        }
    }
    //建立单个猪的查看按钮
    QPushButton *but=new QPushButton[10];
    for(int i=0;i<10;i++)
    {
        but[i].setParent(ui->widget);
        but[i].setGeometry(50+i%2*100,50+i/2*100,70,50);
        but[i].setText(QString("%1").arg(i));
        but[i].setStyleSheet("border-image:url(:/new/prefix1/image/timg (3).jpg)");
    }
    /*QFile judge_file("D:/QTcode/PIG/pig_information.txt");
    if(judge_file.exists()==true)
    {
        judge_file.open(QIODevice::ReadOnly);
        QString ss=judge_file.readLine();
        int sumday;
        int blankcount=0;
        double money;
        int index=-1;
        int index0=-1;
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
        sec=sumday;
        summoney=money;
        for(int i=0;i<100;i++)
        {
            for(int j=0;j<10;j++)
            {
                blankcount=0;

                pigcage[i].cagenumber=i;
                int index1=-1,index2=-1;
                QString ss=judge_file.readLine();
                if(ss=='0')
                {
                    pigcage[i].pigpen[j].blank=true;
                     pigcage[i].pigsum++;
                    continue;
                }
                else{
                    pigcage[i].pigpen[j].blank=false;
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
                            pigcage[i].pigpen[j].pigname=str;
                            if(str=="黑猪")
                            {
                                pigcage[i].blacksum++;
                                pigcage[i].blackpig=true;
                            }else if(str=="白猪")
                            {
                                pigcage[i].whitesum++;
                                pigcage[i].blackpig=false;

                            }else if(str=="花猪")
                            {
                                pigcage[i].flowersum++;
                                pigcage[i].blackpig=false;
                            }
                            str.clear();
                        }else if(blankcount==2)
                        {
                            double tweight=str.toDouble();
                            pigcage[i].pigpen[j].weight=tweight;
                            str.clear();
                        }else if(blankcount==3)
                        {
                            int tday=str.toInt();
                            pigcage[i].pigpen[j].day=tday;
                            str.clear();
                        }else if(blankcount==4)
                        {
                            pigcage[i].pigpen[j].infec=str;
                            str.clear();
                        }
                    }
                }}


            }
        }
        judge_file.close();
    }else
    {*/

   // }

    ui->label->setParent(ui->page_2);
    static int flag=0;
    //进入选中的猪圈
    for(int i=0;i<100;i++)
    {
        connect(btn+i,&QPushButton::clicked,
                [=]()mutable
        {
                flag=i;
                //qDebug()<<i<<" "<<flag;
                ui->label->setStyleSheet("font-size:20px");
                 ui->label->setText(QString("<h1>猪圈编号：%1</h1>"
                                      "<h2>猪的总数：%2</h2>"
                                      "<h3>猪的种类：黑猪|白猪|花猪</h3>"
                                      "<h4>每种数量：%3  |%4 |%5</h4>")
                                    .arg(pigcage[i].cagenumber)
                                    .arg(pigcage[i].pigsum)
                                    .arg(pigcage[i].blacksum)
                                    .arg(pigcage[i].whitesum)
                                    .arg(pigcage[i].flowersum));
                ui->page_2->resize(1000,800);
                ui->page->hide();
                ui->page_2->show();
                //qDebug()<<pigcage[i].cagenumber;

        });
        //qDebug()<<"ad"<<flag;
    }
    //qDebug()<<flag;
    //弹出某个猪的具体情况
    for(int j=0;j<10;j++)
    {
        connect(but+j,&QPushButton::clicked,
                [=]()
        {
            //qDebug()<<pigcage[flag].pigpen[j].pigname;
            QMessageBox::information(this,"详细",QString(

                                               "猪的种类：%2\n"
                                               "猪的重量：%3kg\n"
                                               "饲养时间：%4\n"
                                               "是否感染：%5\n")

                                     .arg(pigcage[flag].pigpen[j].pigname)
                                     .arg(pigcage[flag].pigpen[j].weight)
                                     .arg(pigcage[flag].pigpen[j].day)
                                     .arg(pigcage[flag].pigpen[j].infec));
        });
    }

    //返回键
    connect(ui->button,&QPushButton::clicked,
            [=]()
    {

       ui->page_2->hide();
       ui->page->show();

    });
    //更改背景音乐
    connect(ui->pushButton_6,&QPushButton::clicked,
            [=]()
    {
        QMessageBox::information(this,"更改背景音乐",QString("未实现"));
    });
    //商城控件
    connect(ui->shop,&QPushButton::clicked,
            [=]()
    {
        QMessageBox::information(this,"商城",QString("未实现"));
    });


}

subwidget::~subwidget()
{
    delete ui;
}
void subwidget::paintEvent(QPaintEvent *)
{
    ui->design->setStyleSheet("border-image:url(:/new/prefix1/image/timg (3).jpg)");
    ui->statistic->setStyleSheet("border-image:url(:/new/prefix1/image/timg (3).jpg)");
    ui->shop->setStyleSheet("border-image:url(:/new/prefix1/image/timg (3).jpg)");
    ui->pushButton->setStyleSheet("border-image:url(:/new/prefix1/image/timg (3).jpg)");
    ui->pushButton_2->setStyleSheet("border-image:url(:/new/prefix1/image/timg (3).jpg)");
    ui->pushButton_3->setStyleSheet("border-image:url(:/new/prefix1/image/timg (3).jpg)");
    ui->pushButton_6->setStyleSheet("border-image:url(:/new/prefix1/image/timg (3).jpg)");
    ui->buy_sell->setStyleSheet("border-image:url(:/new/prefix1/image/timg (3).jpg)");
    ui->button->setStyleSheet("border-image:url(:/new/prefix1/image/timg (3).jpg)");
    ui->back2->setStyleSheet("border-image:url(:/new/prefix1/image/timg (3).jpg)");
    ui->back3->setStyleSheet("border-image:url(:/new/prefix1/image/timg (3).jpg)");
    //设置背景
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap(":/new/prefix1/image/timg (2).jpg"));
}
void subwidget::timerEvent(QTimerEvent *)
{
    //输出时间
    ui->lcdNumber->display(++sec);
    //饲养天数与重量按时间增加
    for(int i=0;i<100;i++)
    {
        int a=pigcage[i].pigsum;
        for(int j=0;j<a;j++)
        {
            if(pigcage[i].pigpen[j].pigname==" ")
            {
                a++;
                continue;
            }
            pigcage[i].pigpen[j].day++;
            double addweight=(double)(qrand()%12)/10;
            pigcage[i].pigpen[j].weight+=addweight;
        }
    }
    //总饲养时间满一个月后，猪瘟开始
    if(sec%30==0&&sec!=0)
    {
        //随机一头猪得猪瘟
         qsrand(QTime(0,sec,0).secsTo(QTime::currentTime()));
         int a=qrand()%100;
         int b=qrand()%6;
         pigcage[a].pigpen[b].infection=true;
         pigcage[a].pigpen[b].infec="是";
         pigcage[a].infection=true;
         //qDebug()<<a<<b;

    }
    //猪瘟开始传染
    if(sec>30)
    {
        for(int i=0;i<100;i++)
        {
            if(pigcage[i].infection==true)
            {
                int a=pigcage[i].pigsum;
                for(int j=0;j<a;j++)
                {
                    if(pigcage[i].pigpen[j].pigname==" ")
                    {
                        a++;
                        continue;
                    }
                //本猪圈的传染
                if(pigcage[i].infection==true)
                {
                    qsrand(QTime(0,sec,j).secsTo(QTime::currentTime()));
                    int virus=qrand()%100;
                    if(virus<50&&pigcage[i].pigpen[j].infection==false)
                    {
                        pigcage[i].pigpen[j].infection=true;
                        pigcage[i].pigpen[j].infec="是";
                        //qDebug()<<i<<" "<<j;
                    }else
                    {
                        continue;
                    }

                }
                }
            }else
            {
                continue;
            }

        }
    }
    if(sec>30)
    {
        for(int i=0;i<100;i++)
        {
            int a=pigcage[i].pigsum;
            for(int j=0;j<a;j++)
            {
                if(pigcage[i].pigpen[j].pigname==" ")
                {
                    a++;
                    continue;
                }
                //相邻猪圈感染
                if(i==0)
                {
                    if(pigcage[i+1].infection==true)
                    {
                        int virus=qrand()%100;
                        if(virus<15&&pigcage[i].pigpen[j].infection==false)
                        {
                            pigcage[i].pigpen[j].infection=true;
                            pigcage[i].pigpen[j].infec="是";
                            //qDebug()<<i<<" "<<j;
                        }else
                        {
                            continue;
                        }
                    }
                }else if(i==99)
                {
                    if(pigcage[i-1].infection==true)
                    {
                        int virus=qrand()%100;
                        if(virus<15&&pigcage[i].pigpen[j].infection==false)
                        {
                            pigcage[i].pigpen[j].infection=true;
                            pigcage[i].pigpen[j].infec="是";
                            //qDebug()<<i<<" "<<j;
                        }else
                        {
                            continue;
                        }
                    }
                }else if(i>0&&i<99)
                {
                    if(pigcage[i+1].infection==true||pigcage[i-1].infection==true)
                    {
                        int virus=qrand()%100;
                        if(virus<15&&pigcage[i].pigpen[j].infection==false)
                        {
                            pigcage[i].pigpen[j].infection=true;
                            pigcage[i].pigpen[j].infec="是";
                            //qDebug()<<i<<" "<<j;
                        }else
                        {
                            continue;
                        }
                    }
                }
            }
        }
    }
    badpignumber=0;
    for(int i=0;i<100;i++)
    {
        int a=pigcage[i].pigsum;
        for(int j=0;j<a;j++)
        {
            if(pigcage[i].pigpen[j].pigname==" ")
            {
                a++;
                continue;
            }
            if(pigcage[i].pigpen[j].infection==true)
            {
                badpignumber++;
                pigcage[i].infection=true;
            }
        }
    }
    //qDebug()<<badpignumber;
    ui->label_4->setText(QString("有%1只猪感染").arg(badpignumber));
    //一个月结束进行卖猪与自动补充
    if(sec%90==0&&sec!=0)
    {
        int bsell=0;
        int wsell=0;
        int fsell=0;
        int sumsell=0;
        double bsellmoney=0;
        double wsellmoney=0;
        double fsellmoney=0;
        qsrand(QTime(0,sec,30).secsTo(QTime::currentTime()));
        //遍历猪圈，寻找体重或者饲养时间达标的猪卖出
        for(int i=0;i<100;i++)
        {
            int count=pigcage[i].pigsum;
            for(int j=0;j<count;j++)
            {
                //判断卖出条件
                if((pigcage[i].pigpen[j].weight>150||pigcage[i].pigpen[j].day>360)&&pigcage[i].pigpen[j].infection==false)
                {
                   if(pigcage[i].pigpen[j].pigname=="黑猪")
                   {
                       bsellmoney+=15*pigcage[i].pigpen[j].weight;
                       pigcage[i].blacksum--;
                       bsum--;
                       bsell++;
                   }else if(pigcage[i].pigpen[j].pigname=="花猪")
                   {
                       fsellmoney+=7*pigcage[i].pigpen[j].weight;
                       pigcage[i].flowersum--;
                       fsum--;
                       fsell++;
                   }else if(pigcage[i].pigpen[j].pigname=="白猪")
                   {
                       wsellmoney+=6*pigcage[i].pigpen[j].weight;
                       pigcage[i].whitesum--;
                       wsum--;
                       wsell++;
                   }
                   pigcage[i].pigpen[j].blank=true;
                   pigcage[i].pigpen[j].day=0;
                   pigcage[i].pigpen[j].weight=0;
                   sum--;
                   pigcage[i].pigsum--;
                   pigcage[i].pigpen[j].pigname=" ";
                   pigcage[i].pigpen[j].day=0;
                   pigcage[i].pigpen[j].infection=false;
                   pigcage[i].pigpen[j].infec=" ";
                }//将卖出的猪的数据清0
            }
        }
        int buyw=0;
        int buyf=0;
        //随机自动买入的黑猪
        qsrand(QTime(0,sec,50).secsTo(QTime::currentTime()));
        int buyb=qrand()%(blackcage*10-bsum);

        //随机自动买入的白、花猪
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        int buywf=qrand()%((100-blackcage)*10-wsum-fsum);

        //计算白、花猪的猪圈平均每个猪圈所分的数量
        int wfremainder=(wsum+fsum+buywf)%(100-blackcage);
        int wfaverage=(wsum+fsum+buywf)/(100-blackcage);
        //自动为买入的猪分配猪圈
        for(int i=0;i<100-blackcage;i++)
        {
            int last2=wfremainder;
            if(wfremainder!=0)
            {
                last2=wfaverage+1;
                wfremainder--;
            }
               for(int j=0;j<last2;j++)
            {
            if(pigcage[i].pigpen[j].blank==true)
            {
                sum++;
                pigcage[i].pigpen[j].blank=false;
                pigcage[i].pigpen[j].day=0;
                pigcage[i].pigpen[j].infection=false;
                //qDebug()<<pigcage[i].pigpen[j].infec;
                pigcage[i].pigpen[j].infec="否";
                pigcage[i].pigpen[j].weight=20+qrand()%30;
                pigcage[i].blackpig=false;
                pigcage[i].pigsum++;
                int k=qrand()%2;
                if(k==0)
                {
                    pigcage[i].pigpen[j].pigname="白猪";
                    pigcage[i].whitesum++;
                    wsum++;
                    buyw++;
                 }else
                 {
                    pigcage[i].pigpen[j].pigname="花猪";
                    pigcage[i].flowersum++;
                    fsum++;
                    buyf++;
                 }
             }else
            {
                continue;
            }
            }
         }
            int baverage=(buyb+bsum)/blackcage;
            int bremainder=(buyb+bsum)%blackcage;
            //为自动购入的黑猪分配猪圈
            qsrand(QTime(0,sec,39).secsTo(QTime::currentTime()));
            for(int i=100-blackcage;i<100-blackcage+bremainder;i++)
            {

                for(int j=0;j<=baverage;j++)
                {
                    if(pigcage[i].pigpen[j].blank==true)
                    {
                        pigcage[i].pigpen[j].blank=false;
                        pigcage[i].pigpen[j].day=0;
                        pigcage[i].pigpen[j].infection=false;
                        pigcage[i].pigpen[j].infec="否";
                        pigcage[i].pigpen[j].weight=20+qrand()%30;
                        pigcage[i].blackpig=true;
                        pigcage[i].blacksum++;
                        pigcage[i].pigpen[j].pigname="黑猪";
                        bsum++;
                        pigcage[i].pigsum++;
                    }
                }
                for(int i=100-blackcage+bremainder;i<100;i++)
                {
                    for(int j=0;j<baverage;j++)
                    {
                        if(pigcage[i].pigpen[j].blank==true)
                        {
                            pigcage[i].pigpen[j].blank=false;
                            pigcage[i].pigpen[j].day=0;
                            pigcage[i].pigpen[j].infection=false;
                            pigcage[i].pigpen[j].infec="否";
                            pigcage[i].pigpen[j].weight=20+qrand()%30;
                            pigcage[i].blackpig=true;
                            pigcage[i].blacksum++;
                            pigcage[i].pigpen[j].pigname="黑猪";
                            bsum++;
                            pigcage[i].pigsum++;
                        }
                    }
                }
            }
         buymoney=buyb*210+buyw*190+buyw*195;
         //计算卖猪所获得总的金钱
         sellmoney=bsellmoney+wsellmoney+fsellmoney;
         summoney=summoney+sellmoney-buymoney;
         //计算本次所卖猪的数量
         sumsell=wsell+bsell+fsell;
         //输出本次卖猪的具体情况
         ui->label_2->setStyleSheet("border-image:url(:/new/prefix1/image/timg (3).jpg)");
         ui->label_2->setText(QString("     卖出猪%1头,\n"
                                      "     卖得%2元:\n"
                                      "     黑猪%3头,\n"
                                      "     白猪%4头,\n"
                                      "     花猪%5头")
                              .arg(sumsell)
                              .arg(bsellmoney+wsellmoney+fsellmoney)
                              .arg(bsell)
                              .arg(wsell)
                              .arg(fsell));
         //输出本次自动购猪的具体情况
         ui->label_3->setStyleSheet("border-image:url(:/new/prefix1/image/timg (3).jpg)");
         ui->label_3->setText(QString("     自动购入:\n"
                                      "     白猪%1头,\n"
                                      "     黑猪%2头,\n"
                                      "     花猪%3头,\n"
                                      "     花费%4元")
                              .arg(buyw)
                              .arg(buyb)
                              .arg(buyf)
                              .arg(buymoney));
         //写入购入与卖出信息到文件中]
            QFile file("../PIG/buy_sell.txt");

            bool isOk = file.open(QIODevice::WriteOnly|QIODevice::Append);
            if( isOk==true )
            {
                QTextStream stream(&file);
                stream.setCodec(QTextCodec::codecForName("utf-8"));
                QString str = QString("第 %1 天： \n "
                                      "购入白猪 %2 只,"
                                      "购入黑猪 %3 只,"
                                      "购入花猪 %4 只,"
                                      "共购入 %5 只,"
                                      "支出%6元;\n"

                                      "卖出白猪 %7 只,"
                                      "卖出黑猪 %8 只,"
                                      "卖出花猪 %9 只,"
                                      "共卖出 %10 只,"
                                      "收入%11元;\n"
                                      "所剩余额%12元。\n")
                        .arg(sec).arg(buyw).arg(buyb).arg(buyf).arg(buyw+buyb+buyf).arg(buymoney)
                        .arg(wsell).arg(bsell).arg(fsell).arg(sumsell).arg(sellmoney).arg(summoney);
                stream << str.toUtf8() ;
            }
            file.close();
    }


}
//跳至统计界面
void subwidget::on_statistic_clicked()
{
    //跳转到统计界面
    ui->page_3->resize(1000,800);
    ui->page->hide();
    ui->page_3->show();
    //遍历猪圈，统计猪的体重与饲养天数
    memset(distribution_weight,0,sizeof(distribution_weight));
    memset(distribution_day,0,sizeof(distribution_day));
    for(int i=0;i<100;i++)
    {
        int a=pigcage[i].pigsum;
        for(int j=0;j<a;j++)
        {
            if(pigcage[i].pigpen[j].pigname==" ")
            {
                a++;
                continue;
            }
            distribution_weight[(int)pigcage[i].pigpen[j].weight/30]++;
            distribution_day[(int)pigcage[i].pigpen[j].day/30]++;

        }
    }
    //以30kg为间隔进行分段
    ui->label_weight->setText(QString("重量在  0 ~ 30kg之间的数量：%1\n"
                                      "重量在 30 ~ 60kg之间的数量：%2\n"
                                      "重量在 60 ~ 90kg之间的数量：%3\n"
                                      "重量在 90 ~120kg之间的数量：%4\n"
                                      "重量在120 ~150kg之间的数量：%5\n"
                                      "重量在150 ~180kg之间的数量：%6\n"
                                      "重量在180 ~210kg之间的数量：%7\n"
                                      "重量在210 ~240kg之间的数量：%8")
            .arg(distribution_weight[0])
            .arg(distribution_weight[1])
            .arg(distribution_weight[2])
            .arg(distribution_weight[3])
            .arg(distribution_weight[4])
            .arg(distribution_weight[5])
            .arg(distribution_weight[6])
            .arg(distribution_weight[7]));
    //以30天为间隔进行分段
    ui->lable_day->setText(QString("饲养时间在  0~ 30天：%1\n"
                                   "饲养时间在 30~ 60天：%2\n"
                                   "饲养时间在 60~ 90天：%3\n"
                                   "饲养时间在 90~120天：%4\n"
                                   "饲养时间在120~150天：%5\n"
                                   "饲养时间在150~180天：%6\n"
                                   "饲养时间在180~210天：%7\n"
                                   "饲养时间在210~240天：%8\n"
                                   "饲养时间在240~270天：%9\n"
                                   "饲养时间在270~300天：%10\n"
                                   "饲养时间在300~330天：%11\n"
                                   "饲养时间在330~360天：%12\n"
                                   "饲养时间在360~390天：%13\n"
                                   )
                           .arg(distribution_day[0])
                           .arg(distribution_day[1])
                           .arg(distribution_day[2])
                           .arg(distribution_day[3])
                           .arg(distribution_day[4])
                           .arg(distribution_day[5])
                           .arg(distribution_day[6])
                           .arg(distribution_day[7])
                           .arg(distribution_day[8])
                           .arg(distribution_day[9])
                           .arg(distribution_day[10])
                           .arg(distribution_day[11])
                           .arg(distribution_day[12])
                           );
    connect(ui->back2,&QPushButton::clicked,
            [=]()
    {
            ui->page_3->hide();
            ui->page->show();
    });

}
//跳至设置界面
void subwidget::on_design_clicked()
{
    ui->page_4->resize(1000,800);
    ui->page->hide();
    ui->page_4->show();
    connect(ui->back3,&QPushButton::clicked,
            [=]()
    {
            ui->page_4->hide();
            ui->page->show();
    });
}
//关闭窗口时调用关闭事件
void subwidget::closeEvent(QCloseEvent *e)
{
    //弹出问题对话框
    int ret=QMessageBox::question(this,"关闭","是否需要关闭窗口");
    if(ret==QMessageBox::Yes)
    {
        QFile file_save("../PIG/pig_information.txt");

        bool isok = file_save.open(QIODevice::WriteOnly);
        if(isok==true)
        {
            music_off();
            QTextStream stream(&file_save);
            stream.setCodec(QTextCodec::codecForName("utf-8"));
            //保存运营天数和赚的总金钱
            stream << sec << ' ' << summoney << ' ' << '\n';
            for(int i =0 ;i<100;i++)
            {
                for(int j =0 ;j< 10;j++)
                {
                    //确定猪圈是否为空
                    if(pigcage[i].pigpen[j].blank == 1)
                    {
                        stream << "0\n";
                    }
                    else
                    {
                        //保存每头猪的信息
                        stream << pigcage[i].pigpen[j].pigname<<' ';
                        stream << pigcage[i].pigpen[j].weight << ' ';
                        stream << pigcage[i].pigpen[j].day << ' ';
                        stream << pigcage[i].pigpen[j].infec << ' ';
                        stream << '\n';

                    }
                }
            }
        }
        file_save.close();
        //处理关闭窗口事件，接收事件，终止事件传递
        e->accept();
    }else
    {
        //忽略事件，事件继续给父组件传递
        e->ignore();
    }

}
//显示买入与卖出的信息
void subwidget::on_buy_sell_clicked()
{
    QFile file("D:/QTcode/PIG/buy_sell.txt");
    bool isOk=file.open(QIODevice::ReadOnly);
    if(isOk==true)
    {
        //读文件
        QByteArray array=file.readAll();
        //显示到信息对话框
        QMessageBox::information(this,"买卖记录",QString(array));
    }
    file.close();
}


//采取猪瘟防控措施
void subwidget::on_pushButton_3_clicked()
{
    for(int i=0;i<100;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(pigcage[i].pigpen[j].infection==true)
            {
                badpignumber--;
                if(pigcage[i].pigpen[j].pigname=="黑猪")
                {
                    pigcage[i].pigpen[j].infection=false;
                    pigcage[i].pigpen[j].infec="否";
                    pigcage[i].pigpen[j].blank=true;
                    pigcage[i].pigpen[j].day=0;
                    pigcage[i].pigpen[j].weight=0;
                    pigcage[i].pigpen[j].pigname=" ";
                    pigcage[i].pigsum--;
                    pigcage[i].blacksum--;


                }else if(pigcage[i].pigpen[j].pigname=="白猪")
                {
                    pigcage[i].pigpen[j].infection=false;
                    pigcage[i].pigpen[j].infec="否";
                    pigcage[i].pigpen[j].blank=true;
                    pigcage[i].pigpen[j].day=0;
                    pigcage[i].pigpen[j].weight=0;
                    pigcage[i].pigpen[j].pigname=" ";
                    pigcage[i].pigsum--;
                    pigcage[i].whitesum--;
                }else if(pigcage[i].pigpen[j].pigname=="花猪")
                {
                    pigcage[i].pigpen[j].infection=false;
                    pigcage[i].pigpen[j].infec="否";
                    pigcage[i].pigpen[j].blank=true;
                    pigcage[i].pigpen[j].day=0;
                    pigcage[i].pigpen[j].weight=0;
                    pigcage[i].pigpen[j].pigname=" ";
                    pigcage[i].pigsum--;
                    pigcage[i].flowersum--;
                }
            }
        }
    }
    for(int i=0;i<100;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(pigcage[i].pigpen[j].infection==true)
            {
                break;
            }else if(pigcage[i].pigpen[j].infection==false)
            {
                pigcage[i].infection=false;
            }
        }
    }
}
void subwidget::music_on()
{
     QMediaPlayer *player = new QMediaPlayer;
        connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
        player->setMedia(QUrl::fromLocalFile(":/new/prefix2/Waltzing Leaves.mp3"));
        player->setVolume(30);
        player->play();
    //startmusic->play();
    //startmusic->setLoops(-1);

}
void subwidget::music_off()
{


    //startmusic->stop();
}
