CC = g++
CFLAGS = -Wall -O3 --std=c++11

esercizio02.1.exe : esercizio02.1.o random.o funzionebase.o integral.o 
	$(CC) funzionebase.o random.o integral.o esercizio02.1.o -o esercizio02.1.exe
esercizio02.1.o : esercizio02.1.cpp
	$(CC) -c esercizio02.1.cpp -o esercizio02.1.o $(CFLAGS)
funzionebase.o : funzionebase.cpp funzionebase.h
	$(CC) -c funzionebase.cpp -o funzionebase.o $(CFLAGS)
integral.o : integral.cpp integral.h
	$(CC) -c integral.cpp -o integral.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
clean :
	rm *.o esercizio02.1.exe seed.out
