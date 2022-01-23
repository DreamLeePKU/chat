#include "mainwindow.h"

#include <QApplication>
#include <boost/array.hpp>

typedef boost::array<int,3> array;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//   MainWindow w;
    Chat w;
    w.show();
    return a.exec();
}
