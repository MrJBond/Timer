#ifndef SECONDSARROW_H
#define SECONDSARROW_H
#include "abstractarrow.h"
#include "qgraphicsscene.h"
#include <QGraphicsLineItem>
#include <QObject>
#include <QPainter>

class SecondsArrow : public AbstractArrow
{
public:
    SecondsArrow (QGraphicsScene& scene,qreal& currentX, qreal& currentY,
                 qreal &x2, qreal &y2, qreal &x3, qreal &y3) : AbstractArrow(scene,currentX,currentY,
                                                                        x2, y2, x3, y3) {}
    void drawArrow() override {

        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::red);

        QPolygonF polygon;
        polygon<< QPointF(*x1, *y1) << QPointF(*x2, *y2) << QPointF(*x3, *y3);

        scene->addPolygon(polygon,pen,brush);
    }
};

#endif // SECONDSARROW_H
