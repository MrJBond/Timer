#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "begintimer.h"
#include "clock.h"
#include "clockthread.h"
#include "imagethread.h"
#include "qmediaplayer.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <thread>
#include <future>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButtonStart_clicked();

    void on_pushButtonEnd_clicked();

private:
    Ui::MainWindow *ui;

    QGraphicsScene scene;

    Clock clock;
    ClockThread *clockThread = nullptr;

    chrono::steady_clock::time_point start;
    chrono::steady_clock::time_point end;

    BeginTimer *beginThread = nullptr;

    ImageThread *imageThread = nullptr;

    QMediaPlayer *player = nullptr;
    QAudioOutput *audioOut = nullptr;

public slots:
    void runClock(int type);
    void onMinPassed(int min);
    void changeBeginTimer(int val, int min);
    void onImageChanged(std::string);

};
#endif // MAINWINDOW_H
