#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//#pragma execution_character_set("utf-8")//display chinese words

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <QtWidgets/QMainWindow>
#include <QPaintEvent>
#include <QTimer>
#include <QPainter>
#include <QPixmap>
#include <QLabel>
#include <QImage>
#include <opencv.hpp>
#include "ui_mainwindow.h"
//#include "send_thread.h"
//#include "sender.h"

#include "receiver.h"
#include "send_thread.h"

//class VideoChat;
//class send_thread;
//class VideoChat;

QT_BEGIN_NAMESPACE
namespace Ui { class Chat; }
QT_END_NAMESPACE

//using namespace cv;
//extern VideoChat demo;
//std::string ip = "127.0.0.1";
extern VideoChat demo;
extern send_thread sender_thread;
//class send_thread;
class Chat : public QMainWindow
{
    Q_OBJECT

public:
    Chat(QWidget *parent = nullptr);
    ~Chat();
//    void get_frame(VideoChat& demo);
//    cv::Mat get_frame(VideoChat& demo);


public slots:
    void updataImage();
    void get_ip();
private:
    QTimer theTimer;
    cv::Mat srcImg;
    cv::Mat srcImg_local;
    cv::VideoCapture cap;
    QLabel *ImgLabel;

//    send_thread sender_thread;
    Ui::Chat *ui;
    std::string target_ip;
    bool sender_started;
    bool ready;
//    VideoChat demo;
//    send_thread sender_thread();

protected:
    void paintEvent(QPaintEvent *e);
private slots:
//    void on_checkBox_clicked();
//    void on_pushButton_clicked();
    void send_thread_start();
signals:
    void got_ip();
};
#endif // MAINWINDOW_H
