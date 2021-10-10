#! /bin/sh

# install dependencies
sudo apt install gcc g++ libgtest-dev

# install cmake
sudo apt install cmake

# compile gtest
cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make
 
# copy or symlink libgtest.a and libgtest_main.a to your /usr/lib folder
sudo cp lib/libgtest.a /usr/lib
sudo cp lib/libgtest_main.a /usr/lib
