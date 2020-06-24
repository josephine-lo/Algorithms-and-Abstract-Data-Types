
/*---------------------------------------------------------------------------------
 * Josephine Lo, jowlo, 1689289
 * CSE101 
 * October 29th, 2019
 *---------------------------------------------------------------------------------
 * Matrix.c - Implementation for the Matrix ADT
 *--------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Matrix.h"
#include "List.h"

typedef struct MatrixObj {
	int size;
	int nnz;
	List* row;
} MatrixObj;


// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
// matrix is singly linked list
Matrix newMatrix(int n) {
	if (n < 1) {
		printf("Matrix Error: calling newMatrix() with invalid indices\n");
        exit(EXIT_FAILURE);
	}
	Matrix M = malloc(sizeof(MatrixObj));
	M->size = n;
	M->nnz = 0;
	M->row = malloc(n * sizeof(List));
	for (int i = 0; i < n; i++) {
		M->row[i] = newList();
	}
	return M;
}

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix *pM) {
	if (pM == NULL) {
		printf("Matrix Error: calling freeMatrix() with NULL pointer\n");
		exit(EXIT_FAILURE);
	}

	Matrix M = *pM;
	for(int i = 0; i < M->size; i++) {
		freeList(&(M->row[i]));
	}
	free(M->row);
	M->row = NULL;
	free(*pM);
	pM = NULL;
}


// Access functions
// size()
// Return the size of square Matrix M.
int size(Matrix M) {
	return M->size;
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M) {
	return M->nnz;
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B) {
	int nA = size(A);
	int nnzA = NNZ(A);
	int nB = size(B);
	int nnzB = NNZ(B);
	if (nA == 0 && nB == 0) {
		return 1;
	}
	else if (A == NULL || B == NULL) {
		printf("Matrix Error: calling equals() on NULL Matrix or Matricies");
		exit(EXIT_FAILURE);
	}
	else if (nA != nB || nnzA != nnzB) {
		return 0;
	}

	//Here, we know both size and NNZ are the same for both Matrixes.
	//We then check every list in the Matrix
	for (int i = 0; i < nA; i++) {
		if (equalsList(A->row[i], B->row[i]) < 1) {
            printf("%d\n", i);
            printList(stdout, A->row[i]);
            printf("\n%d\n", i);
            printList(stdout, B->row[i]);
			return 0;
		}
	}
	return 1;

}


// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix.
void makeZero(Matrix M)	{
	int n = M->size;
	M->nnz = 0;
	for (int i = 0; i < n; i++) {
        List L = M->row[i];
        if (L != NULL)
            clear(L);
	}
}


// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x) {
    int n = M->size;
	if (i >= 1 && i <= n && j >= 1 && j <= n) {
        List L = M->row[i - 1];
        if (x != 0){
            int len1 = length(L);
            chgEntry(L, j, x);
            int len2 = length(L);
            if (len2 > len1) M->nnz++;
        } else {
            for (moveFront(L); index(L) >= 0; moveNext(L)) {
                int col = getEntryCol(L);
                if (col == j){
                    delete(L);
                    if (M->nnz > 0)
                        M->nnz--;
                    break;
                } else if (col > j){
                    break;
                }
            }
        }
	}
	else {
		printf("Matrix Error: calling changeEntry() with indices out of range!\n");
        exit(EXIT_FAILURE);
	}
}

// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A) {
	int n = A->size;
	Matrix B = newMatrix(n);
	// traverse List in each row and change the value of each nnz
	for (int i = 0; i < n; i++) {
		List L = A->row[i];
		for (moveFront(L); index(L) >= 0; moveNext(L)) {
			int col = (int) getEntryCol(L);
			double val = (double) getEntryVal(L);
			Entry E = newEntry(col, val);
			append(B->row[i], (void *)E);
		}
	}
	B->nnz = A->nnz;
	B->size = A->size;

	return B;
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A) {
	int n = A->size;
	Matrix B = newMatrix(n);
	// traverse List in each row and change the value of each nnz
	for (int i = 0; i < n; i++) {
		List L = A->row[i];
		for (moveFront(L); index(L) >= 0; moveNext(L)) {
			int ro = i + 1;
			int col = getEntryCol(L);
			double val = getEntryVal(L);
            if (val != 0){
                int temp = ro;
                ro = col - 1;
                col = temp;
                Entry E = newEntry(col, val);
                append(B->row[ro], (void *)E);
            }
		}
	}
    B->size = n;
    B->nnz = A->nnz;
	return B;
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A) {
	int n = A->size;
	Matrix B = newMatrix(n);
    int nnz = 0;
	// traverse List in each row and change the value of each nnz
	for (int i = 0; i < n; i++) {
		List L = A->row[i];
		for (moveFront(L); index(L) >= 0; moveNext(L)) {
			int col = getEntryCol(L);
			double val = x * getEntryVal(L);
            if (val != 0){
                Entry E = newEntry(col, val);
                append(B->row[i], (void *)E);
                nnz++;
            }
		}
	}
    B->nnz = nnz;
    B->size = n;
	return B;
}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B) {
    if(size(A) != size(B)){
        printf("Matrix Error: calling sum() with Matrices of different sizes\n");
        exit(EXIT_FAILURE);
    }
    Matrix C = copy(A);
        // traverse List in each row and change the value of each nnz
    for (int i = 0; i < size(A); i++) {
        List L = B->row[i];
        for (moveFront(L); index(L) >= 0; moveNext(L)) {
            int col = getEntryCol(L);
            double val = getEntryVal(L);
            List L1 = C->row[i];    // C is A now
            int subed = 0;
            for (moveFront(L1); index(L1) >= 0; moveNext(L1)) {
                int col2 = getEntryCol(L1);
                if (col2 == col) {
                    double val2 = getEntryVal(L1) + val;
                    if (val2 == 0){
                        delete(L1);
                        if (C->nnz > 0)
                            C->nnz--;
                    } else {
                        chgEntry(L1, col2, val2);
                    }
                    subed = 1;
                    break;
                }
                else if (col2 > col) {
                    if (val != 0){
                        Entry E = newEntry(col, val);
                        insertBefore(L1, (void *)E);
                        C->nnz++;
                    }
                    subed = 1;
                    break;
                }
            }
            if (!subed) {
                if (val != 0){
                    Entry E = newEntry(col, val);
                    append(L1, (void *)E);
                    C->nnz++;
                }
            }
        }
    }
    return C;
}

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){
	if(size(A) != size(B)){
        printf("Matrix Error: calling diff() on Matrices of different sizes\n");
        exit(EXIT_FAILURE);
    }

	Matrix C = copy(A);
	// traverse List in each row and change the value of each nnz
	for (int i = 0; i < size(A); i++) {
		List L = B->row[i];
		for (moveFront(L); index(L) >= 0; moveNext(L)) {
			int col = getEntryCol(L);
			double val = getEntryVal(L);
			List L1 = C->row[i];	// C is A now
			int subed = 0;
			for (moveFront(L1); index(L1) >= 0; moveNext(L1)) {
				int col2 = getEntryCol(L1);
				if (col2 == col) {
					double val2 = getEntryVal(L1) - val;
                    if (val2 == 0){
                        delete(L1);
                        if (C->nnz > 0){
                            C->nnz--;
                        }
                    } else {
                        chgEntry(L1, col2, val2);
                    }
					subed = 1;
					break;
				}
				else if (col2 > col) {
                    if (val != 0){
                        Entry E = newEntry(col, -val);
                        insertBefore(L1, (void *)E);
                        C->nnz++;
                    }
					subed = 1;
					break;
				}
			}
			if (!subed) {
                if (val != 0){
                    Entry E = newEntry(col, -val);
                    append(L1, (void *)E);
                    C->nnz++;
                }
			}
		}
	}
	return C;
}
    

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B) {
	if(size(A) != size(B)){
        printf("Matrix Error: calling product() on Matrices of different sizes\n");
        exit(EXIT_FAILURE);
    }
	Matrix Bt = transpose(B);
	Matrix C = newMatrix(size(A));
    // go through every list in C
    for (int i = 0; i < size(A); i++){
        for (int j = 0; j < size(A); j++){
            double val = getProdList(A->row[i], Bt->row[j]);
            if (val != 0){
                Entry E = newEntry(j + 1, val);
                append(C->row[i], (void *) E);
                C->nnz++;
            }
        }
    }
    freeMatrix(&Bt);
    return C;
    
}

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M) {
    if (M == NULL){
        printf("Matrix Error: calling printMatrix() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    int n = M->size;
    for (int i = 0; i < n; i++) {
        List L = M->row[i];
        if (L != NULL && length(L) != 0){
            fprintf(out, "%d: ", i + 1);
            printList(out, L);
            fprintf(out, "\n");
        }
    }
}

