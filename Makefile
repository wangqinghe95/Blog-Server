DIR_INC=./include
DIR_SRC=./src
DIR_OBJ=./obj
DIR_BIN=./bin
# DIR_LIB=./lib

# LIBS=-lsw3 -lswofdsdk

SRC = $(wildcard ${DIR_SRC}/*.cpp)
OBJ = $(patsubst %.cpp, ${DIR_OBJ}/%.o, $(notdir ${SRC}))

TARGET=myserver
BIN_TARGET=$(DIR_BIN)/$(TARGET)
INCLUDE=-I ${DIR_INC}
CFLAGS = -g -Wall 

${BIN_TARGET}:${OBJ}
	g++  ${CFLAGS} ${INCLUDE} ${OBJ} -o $@

${DIR_OBJ}/%.o:${DIR_SRC}/%.cpp 
	g++ ${CFLAGS} ${INCLUDE} -c $< -o $@

.PHONY:clean
clean:
	rm -rf ${DIR_OBJ}/*.o ${BIN_TARGET}