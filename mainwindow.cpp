#include "mainwindow.h"
#include <QtDebug>
#include <QInputDialog>
//#include "ui_mainwindow.h"
#include <opencv2\imgproc\types_c.h>
#include <QSharedMemory>
//#include "receiver.cpp"
//#include "send_thread.h"

//#include "send_thread.h"
//#include "sender.h"
//#include "receiver.h"

// for debug
void print(const char* s) {
  std::cout << s << std::endl;
}
// end

Chat::Chat(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Chat),
    sender_started(false),
    ready(false)
{
    ui->setupUi(this);
    connect(&theTimer, &QTimer::timeout, this, &Chat::updataImage);
//    cv::Mat frame = get_frame();
    if(cap.open(0)) {
        srcImg_local = cv::Mat::zeros(cap.get(cv::CAP_PROP_FRAME_HEIGHT),  cap.get(cv::CAP_PROP_FRAME_WIDTH), CV_8UC3);
//    if(true) {
//        srcImg = get_frame();
//    if(sender_started) {
//        theTimer.start(33);
    }
    ImgLabel = new QLabel(this);
    ui->verticalLayout->addWidget(ImgLabel);
    sender_thread.start();
    theTimer.start(33);

    connect(ui->inputIP_btn, &QPushButton::clicked, this, &Chat::get_ip);
    connect(this, &Chat::got_ip, this, &Chat::send_thread_start);
//    connect(ui->pushButton, &QPushButton::clicked, this, &Chat::on_pushButton_clicked);
//    connect(ui->checkBox, &QPushButton::clicked, this, &Chat::on_pushButton_clicked);
//    connect(ui->checkBox, &QCheckBox::toggled, this, &Chat::on_checkBox_clicked);
}

void Chat::send_thread_start() {
//  sender_thread.start();
}
void Chat::paintEvent(QPaintEvent * /*e */) {
    // method 1
    QPainter painter(this);
    QImage image1 = QImage((uchar*)(srcImg.data), srcImg.cols, srcImg.rows, QImage::Format_RGB888);
    painter.drawImage(QPoint(100,100), image1);

//    QPainter painter2(this);
    // 绘制本地摄像头的图像
    QImage image2 = QImage((uchar*)(srcImg_local.data), srcImg_local.cols, srcImg_local.rows, QImage::Format_RGB888);
    painter.drawImage(QPoint(900,100), image2);
    //    method 2
//    ImgLabel->setPixmap(QPixmap::fromImage(image1));
//    ImgLabel->resize(image1.size());
//    ImgLabel->show();

}

void Chat::updataImage() {
    if(!ready) return;
//    std::cout << "u";
    cap >> srcImg_local;
    srcImg = demo.get_frame();
    if(srcImg.data) {
        cvtColor(srcImg, srcImg, CV_BGR2RGB);
        cvtColor(srcImg_local, srcImg_local, CV_BGR2RGB);
        this->update();
    }
}

void Chat::get_ip() {
    bool ok;
    QString name = QInputDialog::getText(this,
                                         tr("IP"),
                                         tr("输入对方IP"),
                                         QLineEdit::Normal,
                                         tr("127.0.0.1"),
                                         &ok);
    qDebug() << "get ip";
    target_ip = name.toStdString();
    sender_started = true;
    ready = true;
//    sender_thread.start();
    emit got_ip();
//    theTimer.start(33);

    QString sharedMessage(name);
    QByteArray sharedData = sharedMessage.toLatin1();

    QSharedMemory* sharedMemory = new QSharedMemory("sharedMemoryKey", this);
    sharedMemory->create(sharedMessage.size());

    sharedMemory->lock();
    memcpy(sharedMemory->data(), sharedData.data(), sharedData.size());
    sharedMemory->unlock();

    return;
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
//    delete ui;
}

