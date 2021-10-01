CC = g++
CFLAGS = -Wall -O3 --std=c++11

esercizio01.1.exe : esercizio01.1.o random.o
	$(CC) random.o esercizio01.1.o -o esercizio01.1.exe
esercizio01.1.o : esercizio01.1.cpp
	$(CC) -c esercizio01.1.cpp -o esercizio01.1.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
clean :
	rm *.o esercizio01.1.exe seed.out
