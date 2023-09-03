
all: clean atividade_1

atividade_1: main.o
	g++ -o main main.o

main.o: main.cpp kernel.h
	g++ -o main.o main.cpp -c -W -Wall -pedantic

kernel.h: file_reader.h process_factory.h

process_factory.h: process.h

clean:
	rm -rf *.o *~ atividade_1
