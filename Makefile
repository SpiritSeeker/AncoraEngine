.PHONY = all clean

CC = g++

LINKERFLAG = -fPIC

ANCORA_DIR = Ancora/src
BIN_DIR = bin/Debug-x64/Ancora
SRCS := $(wildcard ${ANCORA_DIR}/*.h)
CPPS := $(wildcard ${ANCORA_DIR}/Ancora/*.cpp)
BINS := $(patsubst ${ANCORA_DIR}/%.h, ${BIN_DIR}/lib%.so, ${SRCS})

all: ${BINS}

${BINS}: ${SRCS}
	${CC} -shared -o $@ ${LINKERFLAG} $< ${CPPS}

clean:
	rm -rvf ${BIN_DIR}/*.so
