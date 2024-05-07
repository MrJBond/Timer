#ifndef BEGINTIMER_H
#define BEGINTIMER_H

#include "abstractthread.h"
#include "qdebug.h"
#include <QObject>
#include <QThread>
#include <QMutex>
#include <chrono>
#include <thread>

class BeginTimer : public AbstractThread
{
    Q_OBJECT
private:
    int timerVal = 0;
    long long min = 0;

public:
    explicit BeginTimer(QObject *parent = nullptr);

    void run(){

        while(!stop){

             std::this_thread::sleep_for(std::chrono::seconds(1));

            if(stop){
                break;
            }

            if(timerVal == 60){
                min++;
                timerVal = 0;
            }
            timerVal++;
            emit changeNum(timerVal, min);
        }
    }

signals:
    void changeNum(int, int);
};

#endif // BEGINTIMER_H
