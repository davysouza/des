CC=gcc

BUILD_DIR=./build
INCLUDE_DIR=./des/include
CFLAGS=-Wall -g -I${INCLUDE_DIR}

DES_DEPS=des/source/des.c des/include/des.h

OBJS=main.o des.o

all: des_lib test_des clean

des_lib: ${DES_DEPS}
	@echo "Compiling DES library"
	mkdir -p build
	$(CC) ${CFLAGS} -c des/source/des.c

test_des: ${OBJS}
	@echo "Compiling tests"
	mkdir -p build
	$(CC) ${CFLAGS} main.o des.o -o ${BUILD_DIR}/test_des

clean:
	@echo "Cleaning directory"
	rm -f ./*.o ./*.dat

clean_build:
	@echo "Cleaning all build files"
	rm -f ${BUILD_DIR}/*
