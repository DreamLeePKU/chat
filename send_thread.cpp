#pragma once

#include "send_thread.h"

//send_thread::send_thread() {  }

void send_thread::run() {

    // 发送视频
    std::cout << "sending..." << std::endl;
    std::string ip = "127.0.0.1";
    Sender sender(ip);
    while(1) {
        sender.send();
    }
    emit isDone();
}
