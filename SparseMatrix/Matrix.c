/*
 * Ruchit Patel
 * rpatel18
 * pa4
 */

#include <stdio.h>
#include <stdlib.h>

#include "Matrix.h"
#include "List.h"

// private type Entry
typedef struct EntryObj *Entry;

// private EntryObj type
typedef struct EntryObj {
	int col;
	double val;
} EntryObj;

// private MatrixObj type
typedef struct MatrixObj {
	int size;
	int nnz;		// non-zero entries
	List *rows;		// array of rows (lists)
} MatrixObj;

// newEntry()
// Returns a reference to a new EntryObj 
Entry newEntry(int col, double val) {
	Entry E = (Entry) malloc(sizeof(EntryObj));

	if (E) {
		E->col = col;
		E->val = val;
	}

	return E;
}

// freeEntry()
// Free heap memory associated with *E, sets *E to NULL.
void freeEntry(Entry *E) {
	if (E && *E) {
		free(*E);
		*E = NULL;
	}

	return;
}


// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n) {
	Matrix M = (Matrix) malloc(sizeof(MatrixObj));

	if (M) {
		M->size = n;
		M->nnz = 0;
		M->rows = (List *) malloc((n+1) * sizeof(List));
		
		for (int i = 0; i <= n; i++) {
			M->rows[i] = newList();		// initialize rows
		}
	}

	return M;
}
	
// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM) {
	if (pM && *pM) {

		// free all rows
		for (int i = 0; i <= (*pM)->size; i++) {
			//moveFront((*pM)->row[i]);
			freeList(&((*pM)->rows[i]));
		}

		free((*pM)->rows);
		free(*pM);
		*pM = NULL;
	}

	return;
}

// Access functions
// size()
// Return the size of square Matrix M.
int size(Matrix M) {
	if (M == NULL) {
		fprintf(stderr, "Matrix Error: calling size() on NULL Matrix reference.\n");
		exit(ERROR);
	}

	return M->size;
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M) {
	if (M == NULL) {
		fprintf(stderr, "Matrix Error: calling NNZ() on NULL Matrix reference.\n");
		exit(ERROR);
	}

	return M->nnz;
}

// compareEntries()
// private helper function that returns 1 if entries are equal (both values same), else 0
static inline int compareEntries(Entry eA, Entry eB) {
	return (eA->col == eB->col) && (eA->val == eB->val) ? 1 : 0;	// worry about precision later
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B) {

	if (A == NULL || B == NULL) {
		fprintf(stderr, "Matrix Error: calling equals() on NULL Matrix reference.\n");
		exit(ERROR);
	}

	if (A->size != B->size) return 0;

	for (int i = 1; i <= A->size; i++) {				// compare each row
		List rA = A->rows[i], rB = B->rows[i];

		// compare entries row by row
		moveFront(rA); moveFront(rB);
		Entry eA, eB;

		while (index(rA) != -1 && index(rB) != -1) {		// compare till either one ends
			eA = (Entry) get(rA);
			eB = (Entry) get(rB);

			if (compareEntries(eA, eB) == 0) return 0;	// entries not equal

			moveNext(rA); moveNext(rB);
		}

		// both indexes are != -1, meaning one of them has less elements
		if (index(rA) != index(rB)) return 0;
	}

	return 1;
}

// Manipulation procedures

// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M) {

	if (M == NULL) {
		fprintf(stderr, "Matrix Error: calling makeZero() on NULL Matrix reference.\n");
		exit(ERROR);
	}

	// free all rows
	for (int i = 0; i <= M->size; i++) {
		clear(M->rows[i]);		// clear lists
	}

	M->nnz = 0;

	return;

}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x) {

	if (M == NULL) {
		fprintf(stderr, "Matrix Error: calling changeEntry() on NULL Matrix reference.\n");
		exit(ERROR);
	}

	// change range
	if ( (i < 1 || i > M->size) || (j < 1 || j > M->size) ) {
		fprintf(stderr, "Matrix Error: calling changeEntry() with invalid parameters.\n");
		exit(ERROR);
	}

	Entry E = newEntry(j, x);
	List temp = M->rows[i];			// the list that needs to be traversed


	// same algorithm as in pa1 Lex, compare if small move front, find correct place and insert
	Entry eT;
	int found = 0;

	moveBack(temp); 
	while (index(temp) > -1 && j <= ((Entry) get(temp))->col) {
		eT = ((Entry) get(temp));

		// ijth entry != 0, x!= 0. overwrite.
		if (j == eT->col && x != 0.0) {
			freeEntry(&E);			// delete that entry
			//set(temp, (void *) E);		// change entry
			eT->val = x;
			found = 1;
			break;
		}

		// ijth entry != 0, x == 0. delete.
		else if (j == eT->col && x == 0.0) {
			freeEntry(&E);			// no need to for E now
			delete(temp);
			M->nnz--;
			found = 1;
			break;
		}

		movePrev(temp);
	}

	// ijth entry = 0, x != 0. insert.
	if (x != 0.0 && found == 0) {
		
		// cursor becomes undefine. need to prepend (the smallest element)
		if (index(temp) < 0) prepend(temp, (void *) E);
			
		else insertAfter(temp, (void *) E);
		
		M->nnz++;
	}
	
	// ijth entry = 0, x == 0. nothing.
	else if (x == 0.0 && found == 0) {
		if(E) freeEntry(&E);
	}

	return;
}

// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A) {

	if (A == NULL) {
		fprintf(stderr, "Matrix Error: calling copy() on NULL Matrix reference.\n");
		exit(ERROR);
	}

	Matrix M = newMatrix(A->size);

	if (M) {

		List temp;
		Entry etA, etM;

		for (int i = 1; i <= A->size; i++) {
			temp = A->rows[i];
			moveBack(temp);
			// copy every entry in the row
			while(index(temp) >= 0) {
				etA = (Entry) get(temp);
				etM = newEntry(etA->col, etA->val);
				prepend(M->rows[i], etM);
				movePrev(temp);
			}
		}

		M->nnz = A->nnz;
	}


	return M;

}

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A) {

	if (A == NULL) {
		fprintf(stderr, "Matrix Error: calling transpose() on NULL Matrix reference.\n");
		exit(ERROR);
	}

	Matrix M = newMatrix(A->size);


	if (M) {

		List temp;
		Entry eT, copier;

		for(int row = 1; row <= A->size; row++) {
			temp = A->rows[row];
			moveFront(temp);		// traverse row by row
			while (index(temp) >= 0) {
				eT = (Entry) get(temp);
				copier = newEntry(row, eT->val);
				 // process row by row, update column by column
				 // keep appending, order would be maintained
				 // not using changeEntry cause of too many operations
				append(M->rows[eT->col], copier);
				moveNext(temp);
			}
		}	

		M->nnz = A->nnz;
	}


	return M;

}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A) {

	if (A == NULL) {
		fprintf(stderr, "Matrix Error: calling scalarMult() on NULL Matrix reference.\n");
		exit(ERROR);
	}

	Matrix M = newMatrix(A->size);

	if (M) {

		List temp;
		Entry eT, copier;

		// same as transpose
		for (int row = 1; row <= A->size; row++) {
			temp = A->rows[row];
			moveFront(temp);				// traverse row by row
			while (index(temp) >= 0) {
				eT = (Entry) get(temp);
				copier = newEntry(eT->col, x * eT->val);
				append(M->rows[row], copier);	// appending saves time
				moveNext(temp);
			}
		}	

		M->nnz = A->nnz;
	}

	return M;

}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B) {

	if (A == NULL || B == NULL) {
		fprintf(stderr, "Matrix Error: calling sum() on NULL Matrix reference.\n");
		exit(ERROR);
	}

	if (A->size != B->size) {
		fprintf(stderr, "Matrix Error: calling sum() on different size matrices.\n");
		exit(ERROR);
	}

	Matrix M = newMatrix(A->size);

	if (M) {

		/*
		 * if pointers are same, both matrices are same
		 * copy it to avoid moveNext() moving twice
		 */
		Matrix C; 
		int copied = 0;

		if (A==B) {
			C = copy(B);
			copied = 1;
		}
		else {
			C = B;
		}

		double result;
		int col;
		Entry eA, eB, eM;
		List tA, tB;


		for (int row = 1; row <= A->size; row++){

			tA = A->rows[row], tB = C->rows[row];
			moveFront(tA); moveFront(tB);

			while (index(tA) > -1 || index(tB) > -1) {

				result = 0;

				if (index(tA) != -1) eA = get(tA); 
				if (index(tB) != -1) eB = get(tB);

				// a row done, only b left
				if (index(tA) < 0) {
					result = eB->val;
					col = eB->col;
					moveNext(tB);
				}

				// b row done, only a left
				else if (index(tB) < 0) {
					result = eA->val;
					col = eA->col;
					moveNext(tA);
				}

				// a behind
				else if (eA->col < eB->col) {
					result = eA->val;
					moveNext(tA);
					col = eA->col;
				}

				// b behind
				else if (eB->col < eA->col) {
					result = eB->val;
					moveNext(tB);
					col = eB->col;
				}

				// same column
				else if (eB->col == eA->col) {
					result = eA->val + eB->val;
					moveNext(tA); moveNext(tB);
					col = eA->col;
				}

				// add if entry not zero
				if (result != 0) {
					eM = newEntry(col, result);
					append(M->rows[row], eM);
					M->nnz++;
				}
				
			}
		}

		if (copied == 1) freeMatrix(&C);	// free if copied

	}

	return M;
}

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B) {

	if (A == NULL || B == NULL) {
		fprintf(stderr, "Matrix Error: calling diff() on NULL Matrix reference.\n");
		exit(ERROR);
	}

	if (A->size != B->size) {
		fprintf(stderr, "Matrix Error: calling sum() on different size matrices.\n");
		exit(ERROR);
	}

	Matrix M = newMatrix(A->size);

	if (M) {

		/*
		 * if pointers are same, both matrices are same
		 * copy it to avoid moveNext() moving twice
		 */
		Matrix C; 
		int copied = 0;

		if (A==B) {
			C = copy(B);
			copied = 1;
		}
		else {
			C = B;
		}

		double result;
		int col;
		Entry eA, eB, eM;
		List tA, tB;


		for (int row = 1; row <= A->size; row++){

			tA = A->rows[row], tB = C->rows[row];
			moveFront(tA); moveFront(tB);

			while (index(tA) > -1 || index(tB) > -1) {

				result = 0;

				if (index(tA) != -1) eA = get(tA); 
				if (index(tB) != -1) eB = get(tB);

				// a row done, only b left
				if (index(tA) < 0) {
					result = -eB->val;
					col = eB->col;
					moveNext(tB);
				}

				// b row done, only a left
				else if (index(tB) < 0) {
					result = eA->val;
					col = eA->col;
					moveNext(tA);
				}

				// a behind
				else if (eA->col < eB->col) {
					result = eA->val;
					moveNext(tA);
					col = eA->col;
				}

				// b behind
				else if (eB->col < eA->col) {
					result = -eB->val;
					moveNext(tB);
					col = eB->col;
				}

				// same column
				else if (eB->col == eA->col) {
					result = eA->val - eB->val;
					moveNext(tA); moveNext(tB);
					col = eA->col;
				}

				// add if entry not zero
				if (result != 0) {
					eM = newEntry(col, result);
					append(M->rows[row], eM);
					M->nnz++;
				}
				
			}
		}

		if (copied == 1) freeMatrix(&C);	// free if copied
	}

	return M;
}

// vectorDot()
// helper function to return dot product of list A and list B
double vectorDot(List tA, List tB, Matrix M) {
	double result = 0.0;
	moveFront(tA); moveFront(tB);

	Entry eA, eB;

	while (index(tA) > -1 && index(tB) > -1) {

		if (index(tA) != -1) eA = get(tA); 
		if (index(tB) != -1) eB = get(tB);

		// a behind
		if (eA->col < eB->col) moveNext(tA);

		// b behind
		else if (eB->col < eA->col) moveNext(tB);

		// same column
		else {
			result += eA->val * eB->val;
			moveNext(tA); moveNext(tB);
		}

	}

	return result;
}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B) {

	if (A == NULL || B == NULL) {
		fprintf(stderr, "Matrix Error: calling product() on NULL Matrix reference.\n");
		exit(ERROR);
	}

	if (A->size != B->size) {
		fprintf(stderr, "Matrix Error: calling product() on different size matrices.\n");
		exit(ERROR);
	}

	Matrix M = newMatrix(A->size);

	if (M) {

		/*
		 * if pointers are same, both matrices are same
		 * copy it to avoid moveNext() moving twice
		 */
		Matrix C; 
		int copied = 0;

		if (A==B) {
			C = copy(B);
			copied = 1;
		}
		else {
			C = B;
		}

		Matrix bT = transpose(C);

		double result;
		List tA, tB;
		Entry eM;


		for (int row = 1; row <= A->size; row++){

			tA = A->rows[row]; 

			if (length(tA) != 0) {
				for (int col = 1; col <= A->size; col++) {
					result = 0;
					tB = bT->rows[col]; 

					// dot product only if both have non zero entries
					if (length(tB) > 0) result = vectorDot(tA, tB, M);

					if (result != 0) {
						eM = newEntry(col, result);
						append(M->rows[row], eM);
						M->nnz++;
					}
				}
			}
		}

		freeMatrix(&bT);
		if (copied == 1) freeMatrix(&C);	// free if copied
	}

	return M;
}

// printEntry()
// helper function to print values of entry
static inline void printEntry(FILE *out, Entry E) {
	fprintf(out, "(%d, %.1lf) ", E->col, E->val);
}

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M) {
	if (M == NULL) {
		fprintf(stderr, "Matrix Error: Calling printMatrix() on NULL matrix reference.\n");
		exit(ERROR);
	}

	List temp;

	for (int i = 1; i <= M->size; i++) {

		// do not print zero rows
		if ((length(M->rows[i]) != 0)) {
			temp = M->rows[i];
			moveFront(temp);

			fprintf(out, "%d: ", i);
			while (index(temp) != -1) {			// print the whole row
				printEntry(out, get(temp));
				moveNext(temp);
			}
			fprintf(out, "\n");
		}
				
	}

	return;
}
