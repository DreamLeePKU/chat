#include "mainwindow.h"
//#include "ui_mainwindow.h"
#include <opencv2\imgproc\types_c.h>
//#include "receiver.cpp"
//#include "send_thread.h"
#include "send_thread.cpp"

std::string ip = "127.0.0.1";
VideoChat demo(ip);
Chat::Chat(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Chat)
{
    ui->setupUi(this);
    connect(&theTimer, &QTimer::timeout, this, &Chat::updataImage);
//    cv::Mat frame = get_frame();
//    if(cap.open(0)) {
//        srcImg = cv::Mat::zeros(cap.get(cv::CAP_PROP_FRAME_HEIGHT),  cap.get(cv::CAP_PROP_FRAME_WIDTH), CV_8UC3);
//    if(true) {
//        srcImg = get_frame();
    if(true) {
        theTimer.start(33);
    }
    ImgLabel = new QLabel(this);
    ui->verticalLayout->addWidget(ImgLabel);
//    connect(ui->pushButton, &QPushButton::clicked, this, &Chat::on_pushButton_clicked);
//    connect(ui->checkBox, &QPushButton::clicked, this, &Chat::on_pushButton_clicked);
//    connect(ui->checkBox, &QCheckBox::toggled, this, &Chat::on_checkBox_clicked);
    send_thread sender_thread;
    sender_thread.start();

}

void Chat::paintEvent(QPaintEvent *e) {
    // method 1
    QPainter painter(this);
    QImage image1 = QImage((uchar*)(srcImg.data), srcImg.cols, srcImg.rows, QImage::Format_RGB888);
    painter.drawImage(QPoint(20,20), image1);
    //    method 2
//    ImgLabel->setPixmap(QPixmap::fromImage(image1));
//    ImgLabel->resize(image1.size());
//    ImgLabel->show();

}

void Chat::updataImage() {
//    cap >> srcImg;
    srcImg = get_frame(demo);
    if(srcImg.data) {
        cvtColor(srcImg, srcImg, CV_BGR2RGB);
        this->update();
    }
}
//void Chat::on_pushButton_clicked() {
//    srcImg = imread("E:/qt/chat/023.jpg");
//    cvtColor(srcImg, grayImg, CV_BGR2GRAY);

//    Mat tmp;
//    QImage Qtmp;
//    if(!isGray) {
//        cvtColor(srcImg, tmp, CV_BGR2RGB);
//        Qtmp = QImage((const unsigned char*)(tmp.data), tmp.cols, tmp.rows, tmp.step, QImage::Format_RGB888);
//    } else {
//        cvtColor(grayImg, tmp, CV_GRAY2RGB);
//        Qtmp = QImage((const unsigned char*)(tmp.data), tmp.cols, tmp.rows, tmp.step, QImage::Format_RGB888);
//    }
//    ui -> label -> setPixmap(QPixmap::fromImage(Qtmp));
//    ui -> label -> resize(Qtmp.size());
//    ui -> label -> show();
//}
//void Chat::on_checkBox_clicked() {
//    if(ui->checkBox -> isChecked()) {
//        isGray = 1;
//    } else {
//        isGray = 0;
//    }
//}
Chat::~Chat()
{
    delete ui;
}

