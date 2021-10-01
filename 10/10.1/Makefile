CC = g++
CFLAGS = -Wall -O3 --std=c++11

esercizio10.exe : esercizio10.o random.o metropolis.o chromosome.o funzioni.o
	$(CC) random.o esercizio10.o metropolis.o chromosome.o funzioni.o -o esercizio10.exe
esercizio10.o : esercizio10.cpp
	$(CC) -c esercizio10.cpp -o esercizio10.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
metropolis.o : metropolis.cpp metropolis.h
	$(CC) -c metropolis.cpp -o metropolis.o $(CFLAGS)
chromosome.o : chromosome.cpp chromosome.h
	$(CC) -c chromosome.cpp -o chromosome.o $(CFLAGS)
funzioni.o : funzioni.cpp funzioni.h
	$(CC) -c funzioni.cpp -o funzioni.o $(CFLAGS)
clean :
	rm *.o esercizio10.exe seed.out
