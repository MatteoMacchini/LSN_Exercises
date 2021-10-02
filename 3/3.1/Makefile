CC = g++
CFLAGS = -Wall -O3 --std=c++11

esercizio03.1.exe : esercizio03.1.o random.o funzioni.o brownianmotion.o
	$(CC) random.o funzioni.o brownianmotion.o esercizio03.1.o -o esercizio03.1.exe
esercizio03.1.o : esercizio03.1.cpp
	$(CC) -c esercizio03.1.cpp -o esercizio03.1.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
brownianmotion.o : brownianmotion.cpp brownianmotion.h
	$(CC) -c brownianmotion.cpp -o brownianmotion.o $(CFLAGS)
funzioni.o : funzioni.cpp funzioni.h
	$(CC) -c funzioni.cpp -o funzioni.o $(CFLAGS)
esegui:
	./esercizio03.1.exe
clean :
	rm *.o main.exe seed.out
