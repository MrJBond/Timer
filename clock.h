#ifndef CLOCK_H
#define CLOCK_H

#include "baseclock.h"
#include "minutesarrow.h"
#include "secondsarrow.h"
#include <QObject>


using namespace std;

class Clock : public BaseClock
{
private:
    int countIterations;
    int countIterationsMin;
     QGraphicsView* view = nullptr;
     QGraphicsScene* scene;

    vector<pair<qreal, qreal>> bigPoints;
    vector<pair<qreal, qreal>> smallPoints;

    void drawClock();

    void drawAllPoints();

    qreal currentPosX = centerX;
    qreal currentPosY = defaultPoint;
    qreal currentPosXMin = centerX;
    qreal currentPosYMin = defaultPoint;



    qreal currentPosX2Triangle = currentPosX + 6;
    qreal currentPosY2Triangle = currentPosY + 30;
    qreal currentPosX3Triangle = currentPosX;
    qreal currentPosY3Triangle = currentPosY + 30;

    qreal currentPosX2TriangleMin = currentPosX + 6;
    qreal currentPosY2TriangleMin = currentPosY + 30;
    qreal currentPosX3TriangleMin = currentPosX;
    qreal currentPosY3TriangleMin = currentPosY + 30;

    vector<pair<qreal, qreal>> trianglePoints;

public:
    Clock(){

    };
    Clock(QGraphicsView& view){
        this->view = &view;
        this->scene = view.scene();
        view.setEnabled(false);

        drawClock();
        countIterations = 0;
        countIterationsMin = 0;

        SecondsArrow sAr(*scene,currentPosX,currentPosY,
                         currentPosX2Triangle, currentPosY2Triangle,
                         currentPosX3Triangle,currentPosY3Triangle);
        sAr.drawArrow();

        // 450 , 450 center
        scene->addLine(sAr);

        MinutesArrow mAr(*scene,currentPosXMin,currentPosYMin,
                         currentPosX2TriangleMin, currentPosY2TriangleMin,
                         currentPosX3TriangleMin,currentPosY3TriangleMin);
        mAr.drawArrow();

        scene->addLine(mAr);
    };

    void redraw(int type); // to change the clock

};

#endif // CLOCK_H
