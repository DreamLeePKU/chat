#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma execution_character_set("utf-8")//display chinese words

#include <QMainWindow>
#include <opencv2/opencv.hpp>
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
    int isGray = 0;
    Mat srcImg, grayImg;

private:
    Ui::Chat *ui;
private slots:
    void on_checkBox_clicked();
    void on_pushButton_clicked();
};
#endif // MAINWINDOW_H
