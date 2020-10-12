#ifndef CAGE_H
#define CAGE_H

#include <QWidget>
#include <subwidget.h>
class cage : public QWidget
{
    Q_OBJECT
public:
    explicit cage(QWidget *parent = nullptr);
    void dealmysignal(int number);
    subwidget a;
signals:

public slots:
};

#endif // CAGE_H
