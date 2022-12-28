/*
 * Ruchit Patel
 * rpatel18
 * pa4
 */

#include <stdio.h>
#include <stdlib.h>

#include "Matrix.h"

#define ERR 1

// DELTE A, B, IN, OUT

int main(int argc, char *argv[]) {

	// correct number of arguments
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
		exit(ERR);
	}

	// opening files
	FILE *in = fopen(argv[1], "r");
	if (in == NULL) {
		fprintf(stderr, "Unable to open file %s for reading.\n", argv[1]);
		exit(ERR);
	}

	FILE *out = fopen(argv[2], "w");
	if (out == NULL) {
		fprintf(stderr, "Unable to open file %s for writing.\n", argv[2]);
		exit(ERR);
	}

	// get params
	int size, a_nnz, b_nnz;
	fscanf(in, "%d %d %d\n\n", &size, &a_nnz, &b_nnz);

	// make matrices
	Matrix A = newMatrix(size);
	Matrix B = newMatrix(size);

	int row, col; 
	double val;

	// scan in A's entries
	for (int i = 1; i <= a_nnz; i++) {
		fscanf(in, "%d %d %lf", &row, &col, &val);
		changeEntry(A, row, col, val);
	}
	
	// scan in B's entries
	for (int i = 1; i <= b_nnz; i++) {
		fscanf(in, "%d %d %lf", &row, &col, &val);
		changeEntry(B, row, col, val);
	}

	// print A
	fprintf(out, "A has %d non-zero entries:\n", a_nnz);
	printMatrix(out, A);
	fprintf(out, "\n");

	// print B
	fprintf(out, "B has %d non-zero entries:\n", b_nnz);
	printMatrix(out, B);
	fprintf(out, "\n");

	// 1.5 * A
	Matrix scalarA = scalarMult(1.5, A);

	fprintf(out, "(1.5)*A = \n");
	printMatrix(out, scalarA);
	fprintf(out, "\n");
	
	freeMatrix(&scalarA);

	// A+B
	Matrix a_plus_b = sum(A, B);

	fprintf(out, "A+B = \n");
	printMatrix(out, a_plus_b);
	fprintf(out, "\n");
	
	freeMatrix(&a_plus_b);
	
	// A+A
	Matrix a_plus_a = sum(A, A);			// mult by 2.0 wouldve been better 

	fprintf(out, "A+A = \n");
	printMatrix(out, a_plus_a);
	fprintf(out, "\n");
	
	freeMatrix(&a_plus_a);
	
	// B-A
	Matrix b_minus_a = diff(B, A);

	fprintf(out, "B-A = \n");
	printMatrix(out, b_minus_a);
	fprintf(out, "\n");
	
	freeMatrix(&b_minus_a);
	
	// A-A
	Matrix a_minus_a = diff(A, A);	

	fprintf(out, "A-A = \n");
	printMatrix(out, a_minus_a);
	fprintf(out, "\n");
	
	freeMatrix(&a_minus_a);
	
	// Transpose(A)
	Matrix aT = transpose(A);

	fprintf(out, "Transpose(A) = \n");
	printMatrix(out, aT);
	fprintf(out, "\n");
	
	freeMatrix(&aT);
	
	// A*B
	Matrix a_times_b = product(A, B);	

	fprintf(out, "A*B = \n");
	printMatrix(out, a_times_b);
	fprintf(out, "\n");
	
	freeMatrix(&a_times_b);
	
	// B*B
	Matrix b_times_b = product(B, B);	

	fprintf(out, "B*B = \n");
	printMatrix(out, b_times_b);
	fprintf(out, "\n");
	
	freeMatrix(&b_times_b);

	// free memory, close files
	freeMatrix(&A);
	freeMatrix(&B);
	fclose(in);
	fclose(out);
}

