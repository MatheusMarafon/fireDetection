all: main

main: main.o functions.o
	gcc -o main main.o functions.o -lpthread

main.o: main.c
	gcc -c main.c

functions.o: functions.c
	gcc -c functions.c

clean:
	rm *.o main