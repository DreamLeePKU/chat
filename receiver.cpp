#pragma once

#include "global.h"
// send ack
// port1 -> port2 (video data)
// port2 -> port1 (ack data
const int port1 = 12345;
const int port2 = 12346;
const int port3 = 12347;
const int port4 = 12348;
const int maxn = 65535 + 20;
boost::asio::io_context ioc;
class VideoChat {
public:
  int porta;
  int portb;
  int init;
  boost::asio::ip::udp::endpoint ep1; // 要发送到的节点
  boost::asio::ip::udp::endpoint ep2; // 不用设置
  char recv_data[maxn];
  // ip::udp::endpoint
  boost::asio::ip::udp::socket recvSocket;
  boost::asio::ip::udp::socket sendSocket;
  cv::Mat frame2;

  VideoChat(std::string ip1 = "127.0.0.1"):
    porta(port1),
    portb(port2),
    init(1),
    ep1(boost::asio::ip::address::from_string(ip1), port3),
    // ep2(ip::address::from_string(ip1), port4),
    recvSocket(ioc, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port1)),
    sendSocket(ioc, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port2)) {
    memset(recv_data, 0, sizeof(recv_data));
  }

  void send() { // port2 -> 1
    print("sender start");
    int ack = 1;
    while(true) {
      sendSocket.send_to(boost::asio::buffer(&ack, sizeof(ack)), ep1); // 给发送端点确认信息
    }
  }
  void recv() {
//    print("receiver start");
    if(init) {
      init = 0;
      cv::Mat frame;
      cv::VideoCapture cap;
      int deviceID = 0;
      int apiID = cv::CAP_ANY;
      cap.open(deviceID, apiID);
      if (!cap.isOpened()) { std::cerr << "ERROR! Unable to open camera\n"; }
      frame = cv::Mat::zeros(cap.get(cv::CAP_PROP_FRAME_HEIGHT),  cap.get(cv::CAP_PROP_FRAME_WIDTH), CV_8UC3);
      cap.release();
      print("grab2");
      resize(frame, frame2, cv::Size(), 0.25, 0.25);
    }
    int shrinksize = (frame2.dataend - frame2.datastart);
    recvSocket.receive_from(boost::asio::buffer((char*)frame2.data, shrinksize), ep2);
    // text
    // while(1) {
    //   recvSocket.receive_from(buffer(recv_data), ep2);
    //   print("recv from sender: ");
    //   print(recv_data);
    // }
  }
  void start() {
    print("okok");
  }
};


cv::Mat get_frame(VideoChat& demo) {
  demo.recv();
//  demo.send();
  return demo.frame2;
}
