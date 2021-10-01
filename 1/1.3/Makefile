CC = g++
CFLAGS = -Wall -O3 --std=c++11

esercizio01.3.exe : esercizio01.3.o random.o
	$(CC) random.o esercizio01.3.o -o esercizio01.3.exe
esercizio01.3.o : esercizio01.3.cpp
	$(CC) -c esercizio01.3.cpp -o esercizio01.3.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
clean :
	rm *.o esercizio01.3.exe seed.out
