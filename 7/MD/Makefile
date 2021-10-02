CC = g++
CFLAGS = -Wall -O3 --std=c++11

MolDyn_NVE.exe : MolDyn_NVE.cpp MolDyn_NVE.h
	$(CC) MolDyn_NVE.cpp -o MolDyn_NVE.exe

continue : 
	cp config.final config.0
	cp old.final old.0
reset : 
	cp config.fcc config.0
esegui:
	./MolDyn_NVE.exe
clean :
	rm *.o MolDyn_NVE.exe 
