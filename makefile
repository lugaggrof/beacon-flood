all : beacon-flood

beacon-flood: main.o
	g++ -o beacon-flood main.o -ltins
main.o: main.cpp
	g++ -g -c -o main.o main.cpp
clear:
	rm -f *.o beacon_flood
