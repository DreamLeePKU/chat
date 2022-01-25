#ifndef RECEIVER_H
#define RECEIVER_H

//#include "global.h"


//#ifndef GLOBAL_H
//#define GLOBAL_H
#include <QAtomicInteger>

extern QAtomicInteger<bool> receive_init_end;

#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <fstream>
#include <string>
#include <string.h>
#include <queue>
#include <boost/thread.hpp>
#include <stdlib.h>  // rand() 随机整数  1804289383
#include <stdio.h>
#include <iostream>
#include<unistd.h>
// #ifdef _WIN32
#ifdef _WIN64
#include<winsock2.h>
#endif
// #pragma comment(lib, "ws2_32.lib")
//using namespace boost::placeholders;
//using namespace std;

// opencv
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
//using namespace cv;

//using namespace boost::asio;
// using namespace boost::posix_time;

//extern void print(const char* s);
//#endif // GLOBAL_H


// send ack
// port1 -> port2 (video data)
// port2 -> port1 (ack data
const int port1 = 12345;
const int port2 = 12346;
const int port3 = 12347;
const int port4 = 12348;
const int maxn = 65535 + 20;
extern boost::asio::io_context ioc;
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

  VideoChat(std::string ip1 = "127.0.0.1");
  void send();
  void recv();
  void start();
  cv::Mat get_frame();
};



#endif // RECEIVER_H
