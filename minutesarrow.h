#ifndef MINUTESARROW_H
#define MINUTESARROW_H

#include "abstractarrow.h"

class MinutesArrow : public AbstractArrow
{
public:
    MinutesArrow();
    MinutesArrow (QGraphicsScene& scene,qreal& currentX, qreal& currentY,
                 qreal &x2, qreal &y2, qreal &x3, qreal &y3) : AbstractArrow(scene,currentX,currentY,
                        x2, y2, x3, y3) {}
    void drawArrow() override {

        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::green);

        QPolygonF polygon;
        polygon<< QPointF(*x1, *y1) << QPointF(*x2, *y2) << QPointF(*x3, *y3);

        scene->addPolygon(polygon,pen,brush);
    }
};

#endif // MINUTESARROW_H
