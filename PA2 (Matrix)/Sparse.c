/*-----------------------------------------------------------------------
 * Josephine Lo, jowlo, 1689289
 * CSE101
 * October 29th, 2019
 *-----------------------------------------------------------------------
 * Sparse.c - The main program that handles input and output files and
 *	is a client of the Matrix ADT. The Matrix ADT is a client of the
 *	List ADT.
 *----------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "Matrix.h"


int main(int argc, char* argv[]){
    if(argc != 3){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    FILE *in, *out;
    
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if(in == NULL){
       printf("Unable to open file %s for reading\n", argv[1]);
       exit(EXIT_FAILURE);
    }
    if(out == NULL){
       printf("Unable to open file %s for writing\n", argv[2]);
       exit(EXIT_FAILURE);
    }
    int size = 0;
    int n1 = 0;
    int n2 = 0;
    int i = 0;
    int j = 0;
    fscanf(in,"%d %d %d", &size, &n1, &n2);
    
    
    Matrix A = newMatrix(size);
    for(int x = 0; x < n1; x++){
        i = 0;
        j = 0;
        double value = 0.0;
        fscanf(in,"%d %d %lf", &i, &j, &value);
        changeEntry(A, i, j, value);
        //fprintf(out, "\n");
    }
    
    fprintf(out, "A has %d non-zero entries:\n", n1);
    printMatrix(out, A);
    
    Matrix B = newMatrix(size);
    for(int x = 0; x < n2; x++){
        i = 0;
        j = 0;
        double value = 0.0;
        fscanf(in,"%d %d %lf", &i, &j, &value);
        changeEntry(B, i, j, value);
        //fprintf(out, "\n");
    }
    fprintf(out, "\nB has %d non-zero entries:\n", n2);
    printMatrix(out, B);
    
    Matrix C = newMatrix(size);
    C = scalarMult(1.5, A);
    fprintf(out, "\n(1.5)*A =\n");
    printMatrix(out, C);
    
    Matrix D = newMatrix(size);
    D = sum(A, B);
    fprintf(out, "\nA+B =\n");
    printMatrix(out, D);
    
    Matrix E = newMatrix(size);
    E = sum(A, A);
    fprintf(out, "\nA+A =\n");
    printMatrix(out, E);
    
    Matrix F = newMatrix(size);
    F = diff(B, A);
    fprintf(out, "\nB-A =\n");
    printMatrix(out, F);
    
    Matrix G = newMatrix(size);
    G = diff(A, A);
    fprintf(out, "\nA-A =\n");
    printMatrix(out, G);

    Matrix H = newMatrix(size);
    H = transpose(A);
    fprintf(out, "\nTranspose(A) =\n");
    printMatrix(out, H);
    
    Matrix I = newMatrix(size);
    I = product(A, B);
    fprintf(out, "\nA*B =\n");
    printMatrix(out, I);
    
    Matrix J = newMatrix(size);
    J = product(B, B);
    fprintf(out, "\nB*B =\n");
    printMatrix(out, J);
    
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&G);
    freeMatrix(&H);
    freeMatrix(&I);
    freeMatrix(&J);
    
    /* close files */
    fclose(in);
    fclose(out);

    return(0);
    
    
    
}

