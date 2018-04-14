#!/bin/bash -ex

cd /citra

apt-get update
apt-get install -y build-essential libsdl2-dev qtbase5-dev libqt5opengl5-dev qtmultimedia5-dev qttools5-dev qttools5-dev-tools wget git
apt-get install -y libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
apt-get install -y python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libdc1394-22-dev

# Get a recent version of CMake
wget https://cmake.org/files/v3.10/cmake-3.10.1-Linux-x86_64.sh
echo y | sh cmake-3.10.1-Linux-x86_64.sh --prefix=cmake
export PATH=/citra/cmake/cmake-3.10.1-Linux-x86_64/bin:$PATH

# Compile OpenCV from source
git clone https://github.com/opencv/opencv.git
cd opencv
mkdir build && cd build
cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/lib -D BUILD_DOCS=OFF -D BUILD_PERF_TESTS=OFF -D BUILD_TESTS=OFF -D BUILD_WITH_DEBUG_INFO=OFF -D BUILD_opencv_apps=OFF ..
make -j7
make install

cd ..
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DENABLE_QT_TRANSLATION=ON -DCITRA_ENABLE_COMPATIBILITY_REPORTING=${ENABLE_COMPATIBILITY_REPORTING:-"OFF"} -DENABLE_OPENCV=ON -DOpenCV_DIR=/usr/lib/share/OpenCV
make -j4

ctest -VV -C Release
