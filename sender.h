#ifndef SENDER_H
#define SENDER_H

#include "receiver.h"
#include <QtDebug>

extern boost::asio::io_context sender_ioc;
extern QAtomicInteger<bool> rate_ok;

class Sender {
public:
  int ack;
  int porta;
  int portb;
  boost::asio::ip::udp::endpoint ep1; // 要发送到的节点
  boost::asio::ip::udp::endpoint ep2; // 不用设置
  char recv_data[maxn];
  // ip::udp::endpoint
  boost::asio::ip::udp::socket recvSocket;
  boost::asio::ip::udp::socket sendSocket;

  Sender(std::string ip1 = "127.0.0.1");

  void send();
  void recv();
  int get_frame_rate();
};


#endif //
