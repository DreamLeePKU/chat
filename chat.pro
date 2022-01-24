QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    pic.cpp \
    receiver.cpp \
    send_thread.cpp

HEADERS += \
    global.h \
    mainwindow.h \
    pic.h \
    send_thread.h \
    sender.h

FORMS += \
    MatdisplayinQt.ui \
    mainwindow.ui

INCLUDEPATH += E:\op\qt\OpenCV-MinGW-Build-OpenCV-4.5.0-with-contrib\include
INCLUDEPATH += E:\op\qt\OpenCV-MinGW-Build-OpenCV-4.5.0-with-contrib\include\opencv
INCLUDEPATH += E:\op\qt\OpenCV-MinGW-Build-OpenCV-4.5.0-with-contrib\include\opencv2
LIBS += -LE:\op\qt\OpenCV-MinGW-Build-OpenCV-4.5.0-with-contrib\x64\mingw\bin\libopencv_*.dll
LIBS += E:\op\qt\OpenCV-MinGW-Build-OpenCV-4.5.0-with-contrib\x64\mingw\lib\libopencv_*
# for boost
DEPENDPATH += E:\op\boost_qt\boost_1_77_0\boost-mingw\bin\lib
INCLUDEPATH += E:\op\boost_qt\boost_1_77_0\boost-mingw\bin\include\boost-1_77
LIBS += -LE:\op\boost_qt\boost_1_77_0\boost-mingw\bin\lib\*
LIBS += -lws2_32
#LIBS += -lboost_thread
LIBS += E:\op\qt\OpenCV-MinGW-Build-OpenCV-4.5.0-with-contrib\x64\mingw\lib\libboost_thread.a
LIBS += -pthread
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
