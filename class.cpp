//#include <body.h>
//#include <mouth.h>


//Body body;
//Mouth mouth;

#include "receiver.h"
#include "send_thread.h"
#include <QAtomicInteger>

//VideoChat demo;

boost::asio::io_context ioc;
boost::asio::io_context sender_ioc;

std::string ip = "127.0.0.1";
VideoChat demo(ip);

send_thread sender_thread;


QAtomicInteger<bool> receive_init_end(false);
QAtomicInteger<bool> rate_ok(true);
//class send_thread;
