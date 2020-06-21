# install dependencies
sudo apt install gcc g++ libgtest-dev -y

# install cmake
sudo apt-get install cmake -y

# compile gtest
cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make
 
# copy or symlink libgtest.a and libgtest_main.a to your /usr/lib folder
sudo cp *.a /usr/lib
