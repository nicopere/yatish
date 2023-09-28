#!/bin/bash

sudo apt install subversion git cmake g++\
 libwxgtk3.0-gtk3-dev libmysqlclient-dev\
 codeblocks libwxsmithlib0 gettext\
 libfontconfig-dev autoconf doxygen graphviz

mkdir -p ~/sources/gitHub && cd $_
git clone https://github.com/mtangoo/wxDatabase.git
cd wxDatabase
sed -i '/ENABLE_MYSQL/s/OFF/ON/' CMakeLists.txt
sed -i '/ENABLE_SQLITE/s/OFF/ON/' CMakeLists.txt
sed -i '/ENABLE_TDS/s/ON/OFF/' CMakeLists.txt
sed -i '/ENABLE_ODBC/s/ON/OFF/' CMakeLists.txt
cd build
cmake .. # default: -G 'Unix Makefiles'
sudo make install

cd ~/sources/gitHub
git clone https://github.com/utelle/wxpdfdoc.git
cd wxpdfdoc
autoreconf
mkdir build-gtk && cd $_
../configure CXXFLAGS=-O2 # otherwise -g -O2
sudo make install

mkdir -p ~/sources/sourceForge && cd $_
svn checkout https://svn.code.sf.net/p/wxmathplot/svn/trunk wxmathplot
cd wxmathplot/mathplot
sed -i '/MATHPLOT_SHARED/s/OFF/ON/' CMakeLists.txt
mkdir build && cd $_
cmake ..
sudo make install

cd ~/sources/gitHub
git clone https://github.com/iwbnwif/wxFreeChart.git
cd wxFreeChart
for i in include/wx/axis/*.h include/wx/axisplot.h include/wx/xy/xysimpledataset.h sample/xydemos.cpp; do
  sed -i 's/wxOVERRIDE/override/' $i
done
./configure
sudo make install
sudo cp include/wx/chartdc.h /usr/local/include/wx/

cd ~/sources/gitHub
git clone https://github.com/wxIshiko/wxCharts.git
cd wxCharts/samples/candlestick
sed -i 's/WxCandleStick/WxCandlestick/' CMakeLists.txt
cd ../..
sed -i 's/gc.FillPath/\/\/gc.FillPath/' src/wxlinechart.cpp # otherwise third plot hides previous ones (bug)
sed -i '/BUILD_SHARED_LIBS/s/OFF/ON/' CMakeLists.txt
mkdir build-gtk && cd $_
cmake .. -DBUILD_SAMPLES=ON
sudo make install

# HelpBlocks...
