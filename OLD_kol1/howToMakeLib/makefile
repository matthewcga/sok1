
static:
	gcc -Wall -c main.c
	ar rcs libmain.a main.o

shared:
	gcc -Wall -fPIC -c main.c
	gcc -Wall -shared main.o -o libmain.so

///////////////////////////////////////////////////////////

static:
	gcc -Wall -c main.c -o main.o
	ar rcs libmain.a main.o
	gcc -Wall -c main.c -o main.o
	gcc -Wall main.o libmain.a -o main

shared:
	gcc -Wall -fPIC -c main.c -o main.o
	gcc -Wall -shared main.o -o libmain.so
	gcc -Wall -c main.c -o main.o
	gcc -Wall main.o -L ./build -lmain -Wl,-rpath=./build -o main
	
dynamic:
	gcc -Wall -fPIC -c main.c -o main.o
	gcc -Wall -shared main.o -o libmain.so
	gcc -Wall main2.c -o main -ldl