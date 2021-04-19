#!/bin/bash

sudo apt install subversion git cmake g++\
 libwxgtk3.0-dev libmysqlclient-dev\
 codeblocks libwxsmithlib0 gettext
# cmake => make

cd ~/sources/gitHub
git clone https://github.com/nicopere/wxDatabase.git
cd wxDatabase
cd build
cmake .. # default: -G 'Unix Makefiles'
sudo make install

cd ~/sources/gitHub
git clone https://github.com/utelle/wxpdfdoc.git
cd wxpdfdoc
autoreconf
mkdir build-gtk
cd build-gtk
../configure CXXFLAGS=-O2 # otherwise -g -O2 !
sudo make install

# HelpBlocks
