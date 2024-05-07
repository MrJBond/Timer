#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QMediaPlayer>
#include <QAudioOutput>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineEditMin->setAlignment(Qt::AlignRight);
    ui->graphicsView->setScene(&scene);

    clock = Clock(*ui->graphicsView);

    imageThread = new ImageThread();
    connect(imageThread, SIGNAL(changeImg(std::string)), this, SLOT(onImageChanged(std::string)));
    imageThread->stop = false;
    imageThread->start();

    // sound
    player = new QMediaPlayer(this);
    audioOut = new QAudioOutput();
    player->setAudioOutput(audioOut);
    player->setSource(QUrl("qrc:/sound/sound/tic-tac.mp3"));
    audioOut->setVolume(80);
}

MainWindow::~MainWindow()
{
    delete ui;

    if(clockThread){
        clockThread->stop = true;
        clockThread->wait(); // wait the thread to finish
        delete clockThread;
        clockThread = nullptr;
    }

    if(beginThread){
        beginThread->stop = true;
        beginThread->wait();
        delete beginThread;
        beginThread = nullptr;
    }

    if(imageThread){
        imageThread->stop = true;
        imageThread->wait();
        delete imageThread;
        imageThread = nullptr;
    }
    if(player){
        delete player;
        player = nullptr;
    }
    if(audioOut){
        delete audioOut;
        audioOut = nullptr;
    }
}


void MainWindow::on_pushButtonStart_clicked()
{
    start = chrono::steady_clock::now();

    clockThread = new ClockThread();
    clockThread->stop = false;
    connect(clockThread, SIGNAL(timerChanged(int)), this, SLOT(runClock(int)));
    connect(clockThread, SIGNAL(minPassed(int)), this, SLOT(onMinPassed(int)));
    clockThread->start();

    ui->pushButtonStart->setEnabled(false);
    ui->pushButtonEnd->setEnabled(true);

    beginThread = new BeginTimer();
    connect(beginThread, SIGNAL(changeNum(int, int)), this, SLOT(changeBeginTimer(int, int)));
    beginThread->stop = false;
    beginThread->start();
}


void MainWindow::on_pushButtonEnd_clicked()
{
     end = chrono::steady_clock::now();
     auto totalTime = chrono::duration_cast<std::chrono::seconds>(end - start);

    beginThread->stop = true;
    beginThread->quit(); // quit to prevent it from running while waiting for the next thread to finish
    clockThread->stop = true;
    clockThread->wait(); // wait the thread to finish

    if(clockThread){
        delete clockThread;
        clockThread = nullptr;
    }

    if(beginThread){
        delete beginThread;
        beginThread = nullptr;
    }

    QMessageBox box;
    box.setText("Total time is " + QString::number(totalTime.count()) + " seconds");
    box.exec();
    ui->pushButtonStart->setEnabled(true);
    ui->pushButtonEnd->setEnabled(false);
}
void MainWindow::runClock(int type)
{
    if(player->isPlaying()){
        player->stop();
    }
    player->play();
    clock.redraw(type);
}
void MainWindow::onMinPassed(int min){
    clock.redraw(2); // min

    QMessageBox box;
    box.setText("Minutes passed: " + QString::number(min));
    box.exec();
}
void MainWindow::changeBeginTimer(int val, int min){
    ui->lineEdit->setText(QString::number(val));
    ui->lineEditMin->setText(QString::number(min));
}
void MainWindow::onImageChanged(string path){
    QPixmap pix;
    pix.load(QString::fromStdString(path));
    ui->label_2->setPixmap(pix);
}
