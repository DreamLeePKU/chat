#include "receiver.cpp"
//#include "global.h"

//const int maxn = 65000;
//const int port1 = 12345;
//const int port2 = 12346;
//const int port3 = 12347;
//const int port4 = 12348;
boost::asio::io_context sender_ioc;
class Sender {
public:
  int porta;
  int portb;
  int ack;
  boost::asio::ip::udp::endpoint ep1; // 要发送到的节点
  boost::asio::ip::udp::endpoint ep2; // 不用设置
  char recv_data[maxn];
  // ip::udp::endpoint
  boost::asio::ip::udp::socket recvSocket;
  boost::asio::ip::udp::socket sendSocket;

  Sender(std::string ip1 = "127.0.0.1"):
    ack(0),
    porta(port3),
    portb(port4),
    ep1(boost::asio::ip::address::from_string(ip1), port1),
    // ep2(ip::address::from_string(ip1), port2),
    recvSocket(sender_ioc, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port3)),
    sendSocket(sender_ioc, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port4))

  {

    memset(recv_data, 0, sizeof(recv_data));
  }

  void send() {
    print("sender start");

    cv::Mat frame, frame2;
    cv::VideoCapture cap;

    int deviceID = 0;             // 0 = open default camera
    int apiID = cv::CAP_ANY;      // 0 = autodetect default API
    // open selected camera using selected API
    cap.open(deviceID, apiID);
    // check if we succeeded
    if (!cap.isOpened()) {
        std::cerr << "ERROR! Unable to open camera\n";
        return;
    }
    //--- GRAB AND WRITE LOOP
    std::cout << "Start grabbing" << std::endl
        << "Press any key to terminate" << std::endl;
    while(true) {
      // video
      if(ack) {
        cap.read(frame);
        if (frame.empty()) {
          std::cerr << "ERROR! blank frame grabbed\n";
          break;
        }
        // resize(frame, frame2, Size(), 0.01, 0.01);
        // cout << frame2 << endl;
        resize(frame, frame2, cv::Size(), 0.25, 0.25);

        // imshow("Live", frame);
        // char buf[65535];
        // cout << sizeof(frame) << "--" << sizeof(buf);
        // cout << frame;
        // break;
        // frame2 = frame;
        int shrinksize = (frame2.dataend - frame2.datastart);
        sendSocket.send_to(boost::asio::buffer((char*)frame2.data, shrinksize), ep1);
        // cout << shrinksize << "-=-=";
        // break;
        imshow("sender", frame2);
        // print("ok_sender");
//        if (waitKey(20) == 27) { break; }
        ack = 0;
        // break;
        // sleep(1);
//        boost::this_thread::sleep(boost::posix_time::millisec(1000 / 24));
      }

      // only text
      // if(ack) {
      //   print("receive,\n cin");
      //   char buf[maxn];
      //   cin >> buf;
      //   sendSocket.send_to(buffer(buf), ep1);
      //   // sendSocket.send_to(buffer(recv_data), ep2);
      //   ack = 0;
      // }
    }
  }
  void recv() {
    print("receiver start");
    while(1) {
      recvSocket.receive_from(boost::asio::buffer(&ack, sizeof(ack)), ep2);
    }
  }
};
