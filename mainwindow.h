#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma execution_character_set("utf-8")//display chinese words

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

QT_BEGIN_NAMESPACE
namespace Ui { class Chat; }
QT_END_NAMESPACE

using namespace cv;
class Chat : public QMainWindow
{
    Q_OBJECT

public:
    Chat(QWidget *parent = nullptr);
    ~Chat();

public slots:
    void updataImage();
private:
    QTimer theTimer;
    Mat srcImg;
    VideoCapture cap;
    QLabel *ImgLabel;

private:
    Ui::Chat *ui;

protected:
    void paintEvent(QPaintEvent *e);
private slots:
//    void on_checkBox_clicked();
//    void on_pushButton_clicked();
};
#endif // MAINWINDOW_H
