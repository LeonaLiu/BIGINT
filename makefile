test : main.o BigInt.o
	g++ -std=c++11 -o test main.o BigInt.o

main.o : main.cpp BigInt.h
	g++ -std=c++11 -c main.cpp

BigInt.o : BigInt.cpp BigInt.h
	g++ -std=c++11 -c BigInt.cpp

clean : 
	rm test main.o BigInt.o
