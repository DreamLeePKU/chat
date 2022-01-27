//#pragma once

#include "receiver.h"
#include <QtDebug>
//#include <QAtomicInteger>
const bool RESIZE = false;
VideoChat::VideoChat(std::string ip1):
  porta(port1),
  portb(port2),
  init(1),
  ep1(boost::asio::ip::address::from_string(ip1), port3),
  // ep2(ip::address::from_string(ip1), port4),
  recvSocket(ioc, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port1)),
  sendSocket(ioc, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port2)),
  receive_cnt(0),
  error_cnt(0)
{
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
  receive_cnt++;
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
    if(RESIZE)
      resize(frame, frame2, cv::Size(), 0.25, 0.25);
    else {
      resize(frame, frame2, cv::Size(), 1, 1);
    }
    qDebug() << "receiver init end";
  }
  receive_init_end.store(true);
  cv::Mat tmp_frame = frame2;

  int shrinksize = (frame2.dataend - frame2.datastart);
  if(RESIZE)
    recvSocket.receive_from(boost::asio::buffer((char*)frame2.data, shrinksize), ep2);
  else {
    bool frame_complete = true;
    int shrinksize_seg  = shrinksize / 16;
    // 使得每帧图像的起始位置相同
    int ack = 0;
    recvSocket.receive_from(boost::asio::buffer(&ack, sizeof(ack)), ep2);
    qDebug() << ack;
    if(ack != 31415926) return;
    // if(!ack) { qDebug() << "not complete frame"; return; }
    char buf[65000]; 
    for(int i = 0; i < 16; ++i) {
        memset(&buf, 0, sizeof(buf));
        recvSocket.receive_from(boost::asio::buffer(buf), ep2); 
        int index = -1; 
        memcpy(&index, buf, sizeof(int)); 
        if(index != i) {
          qDebug() << "wrong at " << i << endl;
          // memset((char*)(frame2.data), 0, shrinksize); // 接受错误时黑屏
          frame_complete = false;
          frame2 = tmp_frame; // 接受错误时保持原帧
          break; 
        }
        memcpy((char*)(frame2.data + i * shrinksize_seg ),buf + 4, shrinksize_seg); 
    }
    if(!frame_complete) {
      error_cnt++;
      double rer = receive_error_rate();
      if(rer > 0.1) rate_ok.store(false);
      else rate_ok.store(true);
      qDebug() << rer;
    }

  }






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
  return this->frame2;
}

double VideoChat::receive_error_rate() {
    if(receive_cnt < 100) return 1;
    double ans = double(error_cnt) / double(receive_cnt);
    error_cnt = 0;
    receive_cnt = 0;
    return ans;
}
//extern VideoChat demo;
