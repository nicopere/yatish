#!/bin/bash

sudo apt install subversion git cmake make g++\
 libwxgtk3.0-dev libmysqlclient-dev codeblocks libwxsmithlib0

git clone https://github.com/mtangoo/wxDatabase.git
cd wxDatabase
ln -s ../wxdatabase/* ./
./wxDatabase.sh
cmake -G 'Unix Makefiles'
sudo make install
