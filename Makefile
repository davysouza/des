# compiler
CC = gcc

# project paths
BUILD_DIR = ./build
INCLUDE_DIR = ./des/include

# compiler flags
CFLAGS = -fPIC -Wall -g -I${INCLUDE_DIR} -D${BUILD_TYPE}

# lib infos
MAJOR = 0
MINOR = 2
NAME  = simpledes
VERSION = $(MAJOR).$(MINOR)

# build type
BUILD_TYPE ?= RELEASE

# library files
DES_DEPS = des/source/des.c des/include/des.h

# objects
OBJS = main.o des.o

# compiling lib, main_tests and execute tests
all: clean lib tests unit_tests

run_main: clean lib tests unit_tests run_main_tests

run_unit_tests: clean lib tests unit_tests run_unit_tests

# compiling des lib
lib: lib$(NAME).so.$(VERSION)

# compiling main tests
run_main_tests: 
	LD_LIBRARY_PATH=. ./main_tests

run_unit_tests: 
	LD_LIBRARY_PATH=. ./unit_tests

tests: lib$(NAME).so
	$(CC) ${CFLAGS} main.c -o main_$@ -L. -l$(NAME)

unit_tests: lib$(NAME).so
	g++ tests/tests.cpp -I. -I./des/include -lgtest -pthread -L. -l$(NAME) -o unit_tests

# creating a symbolic link for lib
lib$(NAME).so: lib$(NAME).so.$(VERSION)
	ldconfig -v -n .
	ln -s lib$(NAME).so.$(MAJOR) lib$(NAME).so

lib$(NAME).so.$(VERSION): ${DES_DEPS}
	$(CC) ${CFLAGS} -shared -Wl,-soname,lib$(NAME).so.$(MAJOR) $^ -o $@

clean:
	rm -f ./*.o ./*.dat ./*.so.* ./*.so ./main_tests ./unit_tests
