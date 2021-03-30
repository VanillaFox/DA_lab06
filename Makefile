CC=g++

CFLAGS=--std=c++14 -c -O3

all: lb6 

lb6: main.o BigInt.o
	$(CC) main.o BigInt.o -o solution

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

BigInt.o: BigInt.cpp
	$(CC) $(CFLAGS) BigInt.cpp

clean:
	rm -rf *.o solution
