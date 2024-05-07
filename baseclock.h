#ifndef BASECLOCK_H
#define BASECLOCK_H

#include "qgraphicsview.h"
#include <QGraphicsView>
#include <QBrush>

class BaseClock
{
public:
    BaseClock();
protected:
    QBrush brush;
    QPen pen;
    long double PI = acos(-1);

    qreal centerX = 450;
    qreal centerY = 450;
    qreal defaultPoint = 300;

    qreal radius(){
        return sqrt((centerY-defaultPoint)*(centerY-defaultPoint));
    }
};

#endif // BASECLOCK_H
