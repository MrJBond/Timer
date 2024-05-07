#ifndef IMAGETHREAD_H
#define IMAGETHREAD_H

#include "abstractthread.h"
#include "qmutex.h"
#include <QObject>
#include <QThread>
#include <thread>

class ImageThread : public AbstractThread
{
    Q_OBJECT
private:
    int imageCount = 0;
public:
    explicit ImageThread(QObject *parent = nullptr);


    void run(){
        while(!stop){

            imageCount++;

            QMutex mx;
            mx.lock();
            if(stop){
                break;
            }
            mx.unlock();

            std::string im;
            if(imageCount == 1){
                im = ":/img/img/red.png";
            }
            else if(imageCount == 2){
                im = ":/img/img/black.png";
            }else{
                im = ":/img/img/yellow.png";
                imageCount = 0;
            }
            emit changeImg(im);

            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }
signals:
    void changeImg(std::string);

};

#endif // IMAGETHREAD_H
