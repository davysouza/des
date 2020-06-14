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

# compiling lib and main_tests
all: clean lib tests run_main_tests

# compiling des lib
lib: lib$(NAME).so.$(VERSION)

# compiling main tests
run_main_tests: 
	LD_LIBRARY_PATH=. ./main_tests

tests: lib$(NAME).so
	$(CC) ${CFLAGS} main.c -o main_$@ -L. -l$(NAME)

# creating a symbolic link for lib
lib$(NAME).so: lib$(NAME).so.$(VERSION)
	ldconfig -v -n .
	ln -s lib$(NAME).so.$(MAJOR) lib$(NAME).so

lib$(NAME).so.$(VERSION): ${DES_DEPS}
	mkdir -p build
	$(CC) ${CFLAGS} -shared -Wl,-soname,lib$(NAME).so.$(MAJOR) $^ -o $@

clean:
	rm -f ./*.o ./*.dat ./*.so.* ./*.so ./main_tests
