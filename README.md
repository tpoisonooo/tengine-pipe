# tengine-pipe
Tengine 管子是用来快速生产 demo 的辅助工具

## how-to-build

### 编译 Tengine lib

$ git clone https://github.com/OAID/Tengine
$ mkdir build && cd build
$ cmake .. && make

libtengine-lite.so 在 source/libtengine-lite.so，软链到 tengine-pipe

$ cd tengine-pipe
$ ls -s ${Tengine_BUILD}/source/libtengine-lite.so ./

### 下载模型

按照 Tengine 的文档从云盘拉模型下来，目前只是需要 mobilenet_ssd.tmfile，软链过来

$ cd tengine-pipe
$ ls -s ${Models_DIR}/mobilenet_ssd.tmfile ./

### 编译运行

$ ./build.sh
$ LD_PRELOAD=./libtengine-lite.so ./test_preview_ped
