#ifndef CLOCKTHREAD_H
#define CLOCKTHREAD_H

#include "abstractthread.h"
#include <QObject>
#include <QThread>
#include <QMutex>
#include <thread>


class ClockThread : public AbstractThread
{
    Q_OBJECT;
private:
    int countIter = 0;

public:
    ClockThread();

    void run(){

        auto startTime = std::chrono::steady_clock::now();

        if(countIter == 0) // only the first iteration
            std::this_thread::sleep_for(std::chrono::seconds(1)); // To count the first second

        while(!stop){

            QMutex mx;
            mx.lock();

            if(stop){
                break;
            }

            mx.unlock();

            emit timerChanged(1);

            std::this_thread::sleep_for(std::chrono::seconds(1));


            auto timePoint = std::chrono::steady_clock::now();

            // Min
            auto sec = std::chrono::duration_cast<std::chrono::seconds>(timePoint - startTime).count();
            if(sec % 60 == 0){
                emit minPassed(sec / 60);
                countIter++;
            }
        }
    }
signals:
    void timerChanged(int type);
    void minPassed(int min);
};


#endif // CLOCKTHREAD_H
