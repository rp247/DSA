/*
 * Ruchit Patel
 * rpatel18
 * pa4
 */

#include <stdio.h>

#include "Matrix.h"

int main() {
	// constructor test
	Matrix M1 = newMatrix(3);			// 3x3
	Matrix M2 = newMatrix(3);			

	// size test
	printf("Matrix M's size: %d.\n\n", size(M1));	// 3

	/*
	 *       1 2 6 	        3 8 3
	 * M1 =  0 4 1,  M2 =  -1 7 1
	 *       9 0 0          0 0 6 
	 */
	printf("Matrix M's size: %d.\n\n", size(M2));	// 3

	// changeEntry test
	// M1
	// row1
	changeEntry(M1, 1, 1, 1.0); changeEntry(M1, 1, 2, 2.0); changeEntry(M1, 1, 3, 3.0);
	// row2
	changeEntry(M1, 2, 2, 4.0); changeEntry(M1, 2, 3, 1.0);
	// row3
	//changeEntry(M1, 3, 1, 9.0); 
	//changeEntry(M1, 1, 3, 6.0);
	changeEntry(M1, 3, 1, 0.0);

	// makeZero test
	// makeZero(M1);

	// print test
	printf("M1: \n");
	printMatrix(stdout, M1);
	printf("\n");

	printf("Matrix M's size: %d.\n\n", size(M2));	// 3
	
	// changeEntry test
	// M2
	// row1
	changeEntry(M2, 1, 1, 3.0); changeEntry(M2, 1, 2, 8.0); changeEntry(M2, 1, 3, -3.0);
	// row2
	changeEntry(M2, 2, 2, 7.0); changeEntry(M2, 2, 3, 1.0); changeEntry(M2, 2, 1, -1.0);
	// row3
	changeEntry(M2, 3, 3, 5.0); 
	changeEntry(M2, 3, 3, 0.0); 

	// print test
	printf("M2: \n");
	printMatrix(stdout, M2);
	printf("\n");

	// equals test
	printf("M1 == M2? %s.\n", equals(M1, M2) ? "True" : "False");	// False
	
	// copy test
	Matrix M3 = copy(M2);
	printf("M2 == M3? %s.\n\n", equals(M3, M2) ? "True" : "False");	// True

	// transpose test
	Matrix M4 = transpose(M3);
	printf("M4: transpose of (M3 or M2)\n");
	printMatrix(stdout, M4);
	printf("\n");

	// M3 no change
	printf("M3 changed after transpose M4? %s.\n\n", equals(M3, M2) ? "False" : "True"); // False

	// scalarMult test
	Matrix M5 = scalarMult(2.0, M4);
	printf("M5: scalaraMult x2.0 of (M4)\n");
	printMatrix(stdout, M5);
	printf("\n");
	
	// M4 no change
	// printf("M4 changed after scalarMult M5? %s.\n\n", equals(M4, transpose(M3)) ? "False" : "True"); // False

	// sum test
	Matrix M6 = sum(M1, M2);
	printf("M6: sum of (M1 + M2) \n");
	printMatrix(stdout, M6);
	printf("\n");

	// diff test
	Matrix M7 = diff(M1, M2);
	printf("M7: diff of (M1 - M2) \n");
	printMatrix(stdout, M7);
	printf("\n");

	// product test
	Matrix M8 = product(M1, M2);
	printf("M8: product of (M1 * M2) \n");
	printMatrix(stdout, M8);
	printf("\n");

	// destructor test
	freeMatrix(&M1);
	freeMatrix(&M2);
	freeMatrix(&M3);
	freeMatrix(&M4);
	freeMatrix(&M5);
	freeMatrix(&M6);
	freeMatrix(&M7);
	freeMatrix(&M8);

	return 0;
}

