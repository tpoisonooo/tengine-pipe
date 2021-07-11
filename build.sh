g++ -std=c++11 -c test/test_int.cpp
g++ -o test_int test_int.o  -lpthread

g++ -g -O0 -std=c++11 -c test/test_camera_display.cpp `pkg-config --cflags opencv`
g++ -o test_camera_display test_camera_display.o  `pkg-config --libs opencv` -lpthread