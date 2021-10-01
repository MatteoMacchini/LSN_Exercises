CC = g++
CFLAGS = -Wall -O3 --std=c++11

esercizio02.2.exe : esercizio02.2.o random.o
	$(CC) random.o esercizio02.2.o -o esercizio02.2.exe
esercizio02.2.o : esercizio02.2.cpp
	$(CC) -c esercizio02.2.cpp -o esercizio02.2.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
clean :
	rm *.o esercizio02.2.exe seed.out
