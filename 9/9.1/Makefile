CC = g++
CFLAGS = -Wall -O3 --std=c++11

esercizio09.exe : esercizio09.o random.o chromosome.o population.o funzioni.o
	$(CC) random.o chromosome.o population.o funzioni.o esercizio09.o -o esercizio09.exe
esercizio09.o : esercizio09.cpp
	$(CC) -c esercizio09.cpp -o esercizio09.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
funzioni.o : funzioni.cpp funzioni.h
	$(CC) -c funzioni.cpp -o funzioni.o $(CFLAGS)
chromosome.o : chromosome.cpp chromosome.h
	$(CC) -c chromosome.cpp -o chromosome.o $(CFLAGS)
population.o : population.cpp population.h
	$(CC) -c population.cpp -o population.o $(CFLAGS)
esegui:
	./esercizio09.exe
clean :
	rm *.o esercizio09.exe seed.out
