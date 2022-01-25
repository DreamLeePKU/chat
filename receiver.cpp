//#pragma once

#include "receiver.h"
#include <QtDebug>
//#include <QAtomicInteger>

VideoChat::VideoChat(std::string ip1):
  porta(port1),
  portb(port2),
  init(1),
  ep1(boost::asio::ip::address::from_string(ip1), port3),
  // ep2(ip::address::from_string(ip1), port4),
  recvSocket(ioc, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port1)),
  sendSocket(ioc, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port2)) {
  memset(recv_data, 0, sizeof(recv_data));
}

void VideoChat::send() { // port2 -> 1
//  print("sender start");
  int ack = 1;
  while(true) {
    sendSocket.send_to(boost::asio::buffer(&ack, sizeof(ack)), ep1); // 给发送端点确认信息
  }
}

void VideoChat::recv() {
//    print("receiver start");
//    std::cout << recvSocket.;
  if(init) {
    qDebug() << "receiver init...";
    init = 0;
    cv::Mat frame;
    cv::VideoCapture cap;
    int deviceID = 0;
    int apiID = cv::CAP_ANY;
    cap.open(deviceID, apiID);
    if (!cap.isOpened()) { std::cerr << "ERROR! Unable to open camera\n"; }
    frame = cv::Mat::zeros(cap.get(cv::CAP_PROP_FRAME_HEIGHT),  cap.get(cv::CAP_PROP_FRAME_WIDTH), CV_8UC3);
    cap.release();
//    print("grab2");
    resize(frame, frame2, cv::Size(), 0.25, 0.25);
    qDebug() << "receiver init end";
  }
  receive_init_end.store(true);
  int shrinksize = (frame2.dataend - frame2.datastart);
  recvSocket.receive_from(boost::asio::buffer((char*)frame2.data, shrinksize), ep2);

  // text
  // while(1) {
  //   recvSocket.receive_from(buffer(recv_data), ep2);
  //   print("recv from sender: ");
  //   print(recv_data);
  // }
}
void VideoChat::start() {
//  print("okok");
}


cv::Mat VideoChat::get_frame() {
  this->recv();
//  demo.recv();
//  return demo.frame2;
  return this->frame2;
}


//extern VideoChat demo;
