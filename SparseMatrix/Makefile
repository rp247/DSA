#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 4
#
#  make                     makes Sparse
#  make MatrixTest          makes MatrixTest
#  make ListTest            makes ListTest
#  make clean               removes all binaries
#  make SparseCheck         runs Sparse in valgrind on in5
#  make MatrixCheck         runs MatrixTest in valgrind
#  make ListCheck           runs ListTest in valgrind
#------------------------------------------------------------------------------

Sparse: Sparse.o Matrix.o List.o
	gcc -std=c17 -Wall -o Sparse Sparse.o Matrix.o List.o

Sparse.o: Sparse.c Matrix.h
	gcc -std=c17 -Wall -c Sparse.c

Matrix.o: Matrix.c List.c Matrix.h List.h
	gcc -std=c17 -Wall -c Matrix.c List.c

List.o: List.c List.h 
	gcc -std=c17 -Wall -c List.c

MatrixTest: MatrixTest.o Matrix.o List.o
	gcc -std=c17 -Wall -o MatrixTest MatrixTest.o Matrix.o List.o

MatrixTest.o: MatrixTest.c Matrix.c Matrix.h List.c List.h
	gcc -std=c17 -Wall -c MatrixTest.c Matrix.c List.c

ListTest: ListTest.o List.o
	gcc -std=c17 -Wall -o ListTest ListTest.o List.o

ListTest.o: ListTest.c List.c List.h
	gcc -std=c17 -Wall -c ListTest.c List.c

SparseCheck: Sparse
	valgrind --leak-check=full ./Sparse in5 junk5

MatrixCheck: MatrixTest
	valgrind --leak-check=full ./MatrixTest

ListCheck: ListTest
	valgrind --leak-check=full ./ListTest

clean:
	rm -f ./Sparse ./Matrix.o ./List.o ./Sparse.o ./MatrixTest ./MatrixTest.o ./ListTest ./ListTest.o ./SparseCheck ./MatrixCheck ./ListCheck

