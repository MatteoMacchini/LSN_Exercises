CC = g++
CFLAGS = -Wall -O3 --std=c++11

esercizio08.1.exe : esercizio08.1.o random.o funzioni.o funzionebase.o metropolis.o
	$(CC) random.o funzioni.o funzionebase.o metropolis.o esercizio08.1.o -o esercizio08.1.exe
esercizio08.1.o : esercizio08.1.cpp
	$(CC) -c esercizio08.1.cpp -o esercizio08.1.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
funzioni.o : funzioni.cpp funzioni.h
	$(CC) -c funzioni.cpp -o funzioni.o $(CFLAGS)
funzionebase.o : funzionebase.cpp funzionebase.h
	$(CC) -c funzionebase.cpp -o funzionebase.o $(CFLAGS)
metropolis.o : metropolis.cpp metropolis.h
	$(CC) -c metropolis.cpp -o metropolis.o $(CFLAGS)
clean :
	rm *.o esercizio08.1.exe seed.out
