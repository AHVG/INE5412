make clean
make
valgrind --tool=memcheck --leak-check=yes --track-origins=yes -s ./simplefs image.200 200