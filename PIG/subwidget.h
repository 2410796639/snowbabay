#ifndef SUBWIDGET_H
#define SUBWIDGET_H

#include <QWidget>

namespace Ui {
class subwidget;
}

class subwidget : public QWidget
{
    Q_OBJECT

public:
    explicit subwidget(QWidget *parent = 0);
    ~subwidget();
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void closeEvent(QCloseEvent *e);
    int timerID;
    int distribution_weight[8];
    int distribution_day[13];
    double summoney=100000;
    int sum;
    double buymoney;
    double sellmoney;
    int wsum;
    int bsum;
    int fsum;
    int blackcage;
    int sec=0;
    int badpignumber=0;
    struct node
    {
        int pigsum=0;
        int whitesum=0;
        int flowersum=0;
        int blacksum=0;
        int cagenumber=0;
        bool blackpig;
        bool infection;
        struct name
        {
            bool blank=true;
            QString pigname;
            bool infection;
            QString infec;
            double weight=0;
            int day=0;
        }pigpen[10];
    }pigcage[100];
    struct node1
    {
        int weightcount=0;
        int daycount=0;
        QString fenduan;
    }tongji[10];
private:
    Ui::subwidget *ui;

signals:


private slots:
    void on_statistic_clicked();
    void on_design_clicked();
    void on_buy_sell_clicked();

 //   void on_pushButton_3_clicked();
};


#endif // SUBWIDGET_H
