##### 待添加

- 文字消息
- 音频传输

##### 待修改

- 传输视频的大小
- 视频编解码

###### i

Mat传输大的

###### 问题：图像的起始位置有时错误

解决尝试：收发之前先确认 在sender的recv和receiver的send函数里面写

一帧：921600Byte 

cmd

```
C:\mingw64\bin\g++.exe -g -std=c++11 c:\s\op\receiver.cpp -o receiver.o -I E:\op\opencv\build\include -I E:\op\opencv\build\include\opencv2 -I E:\op\opencv\build\include\opencv -I E:\op\new\boost_1_77_0 -L E:\op\opencv\build\x64\MinGW\lib -l opencv_core455 -l opencv_imgproc455 -l opencv_imgcodecs455 -l opencv_video455 -l opencv_ml455 -l opencv_highgui455 -l opencv_objdetect455 -l opencv_flann455 -l opencv_imgcodecs455 -l opencv_photo455 -l opencv_videoio455 -pthread -lws2_32 -lboost_thread

 C:\mingw64\bin\g++.exe -g -std=c++11 c:\s\op\sender.cpp -o sender.o -I E:\op\opencv\build\include -I E:\op\opencv\build\include\opencv2 -I E:\op\opencv\build\include\opencv -I E:\op\new\boost_1_77_0 -L E:\op\opencv\build\x64\MinGW\lib -l opencv_core455 -l opencv_imgproc455 -l opencv_imgcodecs455 -l opencv_video455 -l opencv_ml455 -l opencv_highgui455 -l opencv_objdetect455 -l opencv_flann455 -l opencv_imgcodecs455 -l opencv_photo455 -l opencv_videoio455 -pthread -lws2_32 -lboost_thread
```

