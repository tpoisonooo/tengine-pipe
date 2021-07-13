g++ -O2 -mavx -std=c++11 -c test/test_preview_pedestrian.cpp actor/common/tengine_operations.c
TENGINE_STATIC_PATH='/home/konghuanjun/GitProjects/Tengine/build/source/libtengine-lite-static.a'
g++ -o test_preview_ped -fopenmp test_preview_pedestrian.o  tengine_operations.o  `pkg-config --libs opencv` -lpthread ${TENGINE_STATIC_PATH}

# g++ -std=c++11 -c test/test_int.cpp
# g++ -o test_int test_int.o  -lpthread

# g++ -std=c++11 -c test/test_camera_display.cpp `pkg-config --cflags opencv`
# g++ -o test_camera_display test_camera_display.o  `pkg-config --libs opencv` -lpthread
