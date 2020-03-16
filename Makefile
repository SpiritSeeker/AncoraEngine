.PHONY = all clean

CC = g++

LINKERFLAG = -fPIC

ANCORA_DIR = Ancora/src
BIN_DIR = bin/Debug-x64/Ancora
SRCS := $(wildcard ${ANCORA_DIR}/*.cpp)
BINS := $(patsubst ${ANCORA_DIR}/%.cpp, ${BIN_DIR}/lib%.so, ${SRCS})

all: ${BINS}

${BINS}: ${SRCS}
	${CC} -shared -o $@ ${LINKERFLAG} $<

clean:
	rm -rvf *.so ${BINS} 
