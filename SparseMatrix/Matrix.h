#ifndef MATRIX_H_INCLUDE_
#define MATRIX_H_INCLUDE_

#include <stdio.h>

#define ERROR 1

typedef struct MatrixObj *Matrix;

// Constructors-destructors
Matrix newMatrix(int n);				// Returns a reference to a new nXn Matrix object in the zero state
void freeMatrix(Matrix *pM);				// Frees heap memory associated with *pM, sets *pM to NULL.

// Access functions
int size (Matrix M);					// returns the size of square matrix M.
int NNZ (Matrix M);					// returns the number of non-zero elements in M.
int equals (Matrix A, Matrix B);			// returns true (1) if matrices A and B are equal, 0 otherwise.

// Manipulation procedures
void makeZero (Matrix M);				// returns M to the zero matrix state.
void changeEntry (Matrix M, int i, int j, double x);	// changes M[i, j] to x.

// Matrix Arithmetic operations
Matrix copy (Matrix A);					// returns a reference to a new Matrix which is a copy of A.
Matrix transpose (Matrix A);				// returns a reference to a new Matrix which is transpose of A.
Matrix scalarMult(double x, Matrix A);			// returns a reference to a new Matrix representing xA.
Matrix sum (Matrix A, Matrix B);			// returns a reference to a new Matrix representing A+B.
Matrix diff (Matrix A, Matrix B);			// returns a reference to a new Matrix representing A-B.
Matrix product (Matrix A, Matrix B);			// returns a reference to a new Matrix representing AB.

void printMatrix(FILE *out, Matrix M);			// prints matrix in the specified format.

#endif /* MATRIX_H_INCLUDE_ */
