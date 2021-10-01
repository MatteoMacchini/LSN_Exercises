CC = g++
CFLAGS = -Wall -O3 --std=c++11

esercizio05.exe : esercizio05.o random.o funzioni.o metropolis.o
	$(CC) random.o funzioni.o metropolis.o esercizio05.o -o esercizio05.exe
esercizio05.o : esercizio05.cpp
	$(CC) -c esercizio05.cpp -o esercizio05.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
funzioni.o : funzioni.cpp funzioni.h
	$(CC) -c funzioni.cpp -o funzioni.o $(CFLAGS)
metropolis.o : metropolis.cpp metropolis.h funzionebase.h
	$(CC) -c metropolis.cpp -o metropolis.o $(CFLAGS)
clean :
	rm *.o esercizio05.exe seed.out
