CC=gcc
CFLAGS=-Wall

SRC=triforce.c
OBJ=triforce.o
EXE=triforce
LIBS=-lm

${EXE}: ${OBJ}
	${CC} ${CFLAGS} ${OBJ} ${LIBS} -o ${EXE}

clean:
	rm -f ${OBJ} ${EXE}
