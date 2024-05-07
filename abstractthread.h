#ifndef ABSTRACTTHREAD_H
#define ABSTRACTTHREAD_H

#include <QThread>

class AbstractThread : public QThread
{
public:
    explicit AbstractThread(QObject *parent = nullptr);
    bool stop;
};

#endif // ABSTRACTTHREAD_H
