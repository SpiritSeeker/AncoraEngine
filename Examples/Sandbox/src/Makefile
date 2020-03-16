.PHONY = all clean

BIN_DIR = ../../../bin/Debug-x64/Ancora
INC_DIR = ../../../Ancora/src
CC = g++

SOS := $(wildcard ${BIN_DIR}/*.so)
LIBS := $(patsubst ${BIN_DIR}/lib%.so, -l%, ${SOS})
SRCS := $(wildcard *.cpp)
BINS := $(SRCS:%.cpp=%)

all: ${BINS}

${BINS}: ${SRCS}
	${CC} $< -L${BIN_DIR} ${LIBS} -o $@ -I${INC_DIR}

clean:
	rm -rvf ${BINS}