CC = g++
CFLAGS = -Wall -O3 --std=c++11

esercizio01.2.exe : esercizio01.2.o random.o
	$(CC) random.o esercizio01.2.o -o esercizio01.2.exe
esercizio01.2.o : esercizio01.2.cpp
	$(CC) -c esercizio01.2.cpp -o esercizio01.2.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
clean :
	rm *.o esercizio01.2.exe seed.out
