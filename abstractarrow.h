#ifndef ABSTRACTARROW_H
#define ABSTRACTARROW_H

#include "baseclock.h"
#include <QGraphicsItem>

class AbstractArrow : public QGraphicsItem, public QLineF, public BaseClock
{
public:
    AbstractArrow();

    ~AbstractArrow() = default;

    QRectF boundingRect() const override{
        QRectF r; // to suppress the warning
        return r;
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override{
        Q_UNUSED(painter); // to suppress the warning
        Q_UNUSED(option);
        Q_UNUSED(widget);
        return;
    }

    AbstractArrow(QGraphicsScene& scene,qreal& currentX, qreal& currentY,
                 qreal &x2, qreal &y2, qreal &x3, qreal &y3){
        this->currentPosX = &currentX;
        this->currentPosY = &currentY;
        this->scene = &scene;

        this->x1 = &currentX;
        this->y1 = &currentY;
        this->x2 = &x2;
        this->y2 = &y2;
        this->x3 = &x3;
        this->y3 = &y3;

        drawLine();
    }
    virtual void drawArrow() = 0;

protected:
    qreal *currentPosX = nullptr;
    qreal *currentPosY = nullptr;

    QGraphicsScene* scene;

    // Default polygon pos
    qreal *x1 = nullptr;
    qreal *y1 = nullptr;
    qreal *x2 = nullptr;
    qreal *y2 = nullptr;
    qreal *x3 = nullptr;
    qreal *y3 = nullptr;

    void drawLine(){
        this->setLine(centerX, centerY, *currentPosX, *currentPosY);
    }

};

#endif // ABSTRACTARROW_H
