make all
valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./bin/atividade_2 4 < ./entradas/entrada.txt