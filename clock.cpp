#include "clock.h"
#include <QGraphicsLineItem>
#include "secondsarrow.h"

void Clock::drawClock(){
    scene->addEllipse(300,300,300,300,QPen(Qt::white),brush);
    drawAllPoints();
}

void Clock::drawAllPoints(){

    // For big points
    // From 12:00
    for(double fi = PI+PI/2; fi<PI+PI/2 + 2*PI; fi += PI/6){
        qreal x = radius() * cos(fi) + centerX;
        qreal y = radius() * sin(fi) + centerY;
        bigPoints.push_back(make_pair(x,y));
    }

    for(auto p : bigPoints){
        scene->addEllipse(p.first, p.second, 10, 10, QPen(Qt::red), QBrush(Qt::red));
    }

    // For small points
    for(double fi = PI+PI/2; fi < PI+PI/2 + 2*PI; fi += PI/30){
        qreal x = radius() * cos(fi) + centerX;
        qreal y = radius() * sin(fi) + centerY;
        smallPoints.push_back(make_pair(x,y));
    }
    // push the first point to the end to draw properly when the entire circle has been passed
    smallPoints.push_back(make_pair(smallPoints[0].first,smallPoints[0].second));

    for(auto p : smallPoints){
        scene->addEllipse(p.first, p.second, 5, 5, QPen(Qt::red), QBrush(Qt::red));
    }

    // Find all points for the triangle

    for(double fi = PI+PI/2; fi<PI+PI/2 + 2*PI; fi += PI/60){
        qreal x = (radius()-30) * cos(fi) + centerX;
        qreal y = (radius()-30) * sin(fi) + centerY;
        trianglePoints.push_back(make_pair(x,y));
    }

    // draw numbers
    int counter = 1;
    for(double fi = PI+PI/2 + PI/6; fi < PI+PI/2+2*PI; fi += PI/6){
        qreal x = (radius()+25) * cos(fi) + centerX;
        qreal y = (radius()+25) * sin(fi) + centerY;

        QGraphicsTextItem* text = scene->addText(QString::number(counter),QFont("Times", 10, QFont::Bold));
        text->setDefaultTextColor(Qt::white);
        text->setPos(x,y);
        counter++;
    }
}

void Clock::redraw(int type){
    // 1 - for seconds
    // 2 - for minutes
    if(type == 1){
        // if the entire circle was passed
        if(currentPosX == smallPoints[smallPoints.size()-1].first && currentPosY == smallPoints[smallPoints.size()-1].second){
            currentPosX = smallPoints[0].first;
            currentPosY = smallPoints[0].second;
        }

        // Remove previous line
        for(auto& item : scene->items()){

            // So it is seconds arrow
            if(dynamic_cast<MinutesArrow*>(item) == nullptr){
                scene->removeItem(item);
            }
        }
        // find the next point
        for(size_t i = 0; i < smallPoints.size(); i++){
            if(smallPoints[i].first == currentPosX && smallPoints[i].second == currentPosY && i != smallPoints.size()-1){
                currentPosX = smallPoints[i+1].first;
                currentPosY = smallPoints[i+1].second;
                break;
            }
        }
        countIterations += 1;

        SecondsArrow sAr(*scene,currentPosX,currentPosY,
                         trianglePoints[2*countIterations].first, trianglePoints[2*countIterations].second,
                         trianglePoints[2*countIterations+1].first,trianglePoints[2*countIterations+1].second);
        sAr.drawArrow();

        scene->addLine(sAr);

        // Draw on the same pos
        MinutesArrow mAr(*scene,currentPosXMin,currentPosYMin,
                         currentPosX2TriangleMin, currentPosY2TriangleMin,
                         currentPosX3TriangleMin,currentPosY3TriangleMin);
        mAr.drawArrow();
        scene->addLine(mAr);
    }
    if(type == 2){ // min

        // if the entire circle was passed
        if(currentPosXMin == bigPoints[bigPoints.size()-1].first && currentPosYMin == bigPoints[bigPoints.size()-1].second){
            currentPosXMin = bigPoints[0].first;
            currentPosYMin = bigPoints[0].second;
        }

        // Remove previous line
        for(auto& item : scene->items()){
            // So it is min arrow
            if(dynamic_cast<SecondsArrow*>(item) == nullptr){
                scene->removeItem(item);
            }
        }

        // find the next point
        for(size_t i = 0; i < bigPoints.size(); i++){
            if(bigPoints[i].first == currentPosXMin && bigPoints[i].second == currentPosYMin && i != bigPoints.size()-1){
                currentPosXMin = bigPoints[i+1].first;
                currentPosYMin = bigPoints[i+1].second;
                break;
            }
        }
        countIterationsMin += 1;

        MinutesArrow mAr(*scene,currentPosXMin,currentPosYMin,
                         trianglePoints[10*countIterationsMin].first, trianglePoints[10*countIterationsMin].second,
                         trianglePoints[10*countIterationsMin+1].first,trianglePoints[10*countIterationsMin+1].second);

        // memorize current min pos
        currentPosX2TriangleMin = trianglePoints[10*countIterationsMin].first;
        currentPosY2TriangleMin = trianglePoints[10*countIterationsMin].second;
        currentPosX3TriangleMin = trianglePoints[10*countIterationsMin+1].first;
        currentPosY3TriangleMin = trianglePoints[10*countIterationsMin+1].second;

        mAr.drawArrow();
        scene->addLine(mAr);
    }
    drawClock(); // Draw again
}
