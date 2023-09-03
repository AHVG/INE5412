
all: atividade_1

atividade_1: main.o
    g++ -o main main.o

main.o: main.cpp kernel.h
    g++ -o main.o main.cpp -c -W -Wall -ansi -pedantic

clean:
    rm -rf *.o *~ atividade_1
