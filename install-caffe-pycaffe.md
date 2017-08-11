在Ubuntu16.04上安装Caffe和PyCaffe
=====
注：在已经安装好Ubuntu 16.04，cuda的电脑上安装。\
参考网址：http://caffe.berkeleyvision.org/installation.html

### 安装
```shell
# pre-requirements
sudo apt-get install libprotobuf-dev libleveldb-dev \
libsnappy-dev libopencv-dev libhdf5-serial-dev protobuf-compiler
sudo apt-get install --no-install-recommends libboost-all-dev

cd ~
git clone https://github.com/BVLC/caffe.git
cd caffe
cp Makefile.config.example Makefile.config

# set up Makefile.config
make all -j4
make test -j4
make runtest -j4

# install pycaffe
make pycaffe
# add the pycaffe path to ~/.bashrc PYTHONPATH
# export PYTHONPATH=/home/yourname/caffe/python:$PYTHONPATH
# launch a new terminal and try to import caffe
```
#### 问题及解决方案
1. make error: can't find hdf5.h
具体报错：
```txt
CXX src/caffe/util/upgrade_proto.cpp
In file included from src/caffe/util/upgrade_proto.cpp:10:0:
./include/caffe/util/io.hpp:8:18: fatal error: hdf5.h: no such file or directory
 #include "hdf5.h"
                  ^
compilation terminated.
```
原因：Ubuntu的hdf5位置未添加正确，应该在/usr/include/hdf5/serial/中
解决方法：
```txt
INCLUDE_DIRS := $(PYTHON_INCLUDE) /usr/local/include /usr/include/hdf5/serial/
```

2. make error: cannot find -lhdf5_hl -lhdf5
具体报错:
```txt
/usr/bin/ld: cannot find -lhdf5_hl
/usr/bin/ld: cannot find -lhdf5
```
原因，Ubuntu的hdf5库有后缀'serial'，名字不同，所以找不到库。创建快捷方式即可
解决方法：
```shell
cd /usr/lib/x86_64-linux-gnu
# especially check your libhdf5_serial.so.xxx name
sudo ln -s libhdf5_serial.so.10.1.0 libhdf5.so
sudo ln -s libhdf5_serial_hl.so.10.0.2 libhdf5_hl.so
```
3. make runtest error: error == cudaSuccess (38 vs. 0) no CUDA-capable device is detected 
确保CUDA_DIR的设置是正确的，若正确，则试试`nvidia-smi`是否能够正常运行，
若不能正常运行，重启电脑，`make runtest`

4. make pycaffe error: cannot find numpy arrayobject.h
原因：PYTHON_INCLUDE设置不对，如果是用的系统自带的python，查看下arrayobject.h的位置，
在`/usr/lib/python2.7/dist-packages/numpy/core/include` or
`/usr/local/lib/python2.7/dist-packages/numpy/core/include`
