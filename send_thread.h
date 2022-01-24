#ifndef SEND_THREAD_H
#define SEND_THREAD_H

#include <QThread>
#include "sender.h"
class send_thread: public QThread {
    Q_OBJECT
public:
//    send_thread();
    send_thread(QObject *parent = 0);

protected:
    void run();

signals:
    void isDone();

};

#endif // SEND_THREAD_H
