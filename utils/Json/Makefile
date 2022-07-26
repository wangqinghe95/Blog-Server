DIR_INC=.
DIR_SRC=.
DIR_OBJ:=./obj

SRC = $(wildcard ${DIR_SRC}/*.cpp)
OBJ = $(patsubst %.cpp, ${DIR_OBJ}/%.o, $(notdir ${SRC}))

TARGET=JSON
BIN_TARGET=$(TARGET)
INCLUDE=-I ${DIR_INC}
CFLAGS = -g -Wall -std=c++11

All:obj ${BIN_TARGET}

${BIN_TARGET}:${OBJ}
	g++  ${CFLAGS} ${INCLUDE} ${OBJ} ${LIBS} -o $@

${DIR_OBJ}/%.o:${DIR_SRC}/%.cpp 
	g++ ${CFLAGS} ${INCLUDE} -c $< -o $@

obj:
	mkdir -p $@

.PHONY:clean
clean:
	rm -rf ${DIR_OBJ}/*.o ${BIN_TARGET}