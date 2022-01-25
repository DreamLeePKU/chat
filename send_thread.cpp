//#pragma once

#include "send_thread.h"
#include <QtDebug>
#include <QInputDialog>
#include <QSharedMemory>
send_thread::send_thread(QObject*parent):QThread(parent) {  }

#include "mainwindow.h"

//extern Chat w;

void send_thread::run() {

    // 发送视频
    std::cout << "sending..." << std::endl;
    std::string ip = "127.0.0.1";
    // ip待修改
//    bool ok;
//    QString name = QInputDialog::getText(&w,
//                                         tr("IP"),
//                                         tr("输入对方IP"),
//                                         QLineEdit::Normal,
//                                         tr("127.0.0.1"),
//                                         &ok);
    // share memory begin
    QString sharedMessage;
    while(sharedMessage == "") {
      QSharedMemory* sharedMemory = new QSharedMemory("sharedMemoryKey", this);
      sharedMemory->attach();
      sharedMemory->lock();
      QByteArray sharedData(sharedMemory->size(), '\0');

      memcpy(sharedData.data(), sharedMemory->data(), sharedMemory->size());
      sharedMemory->unlock();

      sharedMessage = QString::fromLatin1(sharedData);
      qDebug() << "get: " << sharedMessage;
      sharedMemory->detach();
      sleep(1);
    }
    // end
    qDebug() << "get ip in run thread";
    ip = sharedMessage.toStdString();
//    sleep(30);
    while(!receive_init_end.load()) {
      qDebug() << "wait for receiver to init...";
       sleep(2);
    }
//    while(true) {
//        try {
//          Sender sender(ip);
//          while(1) sender.send();
//        }  catch (...) {
//          sleep(2);
//        }
//    }
    Sender sender(ip);
    while(1) {
        sender.send();
    }
    emit isDone();
}

