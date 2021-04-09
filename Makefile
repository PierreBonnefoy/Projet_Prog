OPTIONS=-Wall -std=c89 -pedantic -O3

compiler:partie1.o
	gcc $(OPTIONS) partie1.o -o partie1

partie1.o:partie1.c partie1.h
	gcc $(OPTIONS) partie1.c -c

clean:
	rm -rf *.o *~
