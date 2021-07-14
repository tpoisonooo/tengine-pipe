g++ -O0 -g -mavx -mfma -std=c++11 -c test/test_preview_pose_estimation.cpp
g++ -o test_preview_pose -fopenmp test_preview_pose_estimation.o  tengine_operations.o  `pkg-config --libs opencv` -lpthread -L./ -ltengine-lite

# g++ -std=c++11 -c test/test_int.cpp
# g++ -o test_int test_int.o  -lpthread

# g++ -std=c++11 -c test/test_camera_display.cpp `pkg-config --cflags opencv`
# g++ -o test_camera_display test_camera_display.o  `pkg-config --libs opencv` -lpthread
