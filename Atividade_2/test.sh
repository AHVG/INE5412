make all
valgrind --tool=memcheck --leak-check=yes --track-origins=yes -s ./bin/simulador 4 < ./entradas/vsim-gcc.txt