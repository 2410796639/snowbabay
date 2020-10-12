#include "cage.h"
#include <cstdlib>
#include <ctime>
#include <QPushButton>
#include <QLabel>

cage::cage(QWidget *parent) : QWidget(parent)
{
    this->setStyleSheet("border-image:url(:/new/prefix1/image/widget.jpg)");

    resize(600,400);
    QPushButton *but=new QPushButton [10];
    for(int i=0;i<10;i++)
    {
        but[i].setParent(this);
        but[i].setGeometry(50+i%2*50,50+i/2*50,50,50);
        but[i].setText(QString("%1").arg(i));
        but[i].show();

    }

    connect(&a,&subwidget::mysignal,this,&cage::dealmysignal());
}

