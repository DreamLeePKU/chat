#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2\imgproc\types_c.h>

Chat::Chat(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Chat)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &Chat::on_pushButton_clicked);
    connect(ui->checkBox, &QPushButton::clicked, this, &Chat::on_pushButton_clicked);
    connect(ui->checkBox, &QCheckBox::toggled, this, &Chat::on_checkBox_clicked);

}

void Chat::on_pushButton_clicked() {
    srcImg = imread("E:/qt/chat/023.jpg");
    cvtColor(srcImg, grayImg, CV_BGR2GRAY);

    Mat tmp;
    QImage Qtmp;
    if(!isGray) {
        cvtColor(srcImg, tmp, CV_BGR2RGB);
        Qtmp = QImage((const unsigned char*)(tmp.data), tmp.cols, tmp.rows, tmp.step, QImage::Format_RGB888);
    } else {
        cvtColor(grayImg, tmp, CV_GRAY2RGB);
        Qtmp = QImage((const unsigned char*)(tmp.data), tmp.cols, tmp.rows, tmp.step, QImage::Format_RGB888);
    }
    ui -> label -> setPixmap(QPixmap::fromImage(Qtmp));
    ui -> label -> resize(Qtmp.size());
    ui -> label -> show();
}
void Chat::on_checkBox_clicked() {
    if(ui->checkBox -> isChecked()) {
        isGray = 1;
    } else {
        isGray = 0;
    }
}
Chat::~Chat()
{
    delete ui;
}

