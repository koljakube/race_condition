CC=gcc
CFLAGS=-c -Wall
LDFLAGS=-pthreads

all: race_condition
	
race_condition: main.o race_condition.o
	${CC} ${LDFLAGS} main.o race_condition.o -o race_condition

main.o:
	${CC} ${CFLAGS} main.c

race_condition.o:
	${CC} ${CFLAGS} race_condition.c

clean:
	rm -rf *.o race_condition
