
/*---------------------------------------------------------------------------------
 * Josephine Lo, jowlo, 1689289
 * CSE101 
 * October 29th, 2019
 *---------------------------------------------------------------------------------
 * MatrixTest.c - A test file to test the functions of the Matrix ADT
 *--------------------------------------------------------------------------------*/

#include<stdio.h>
#include<stdlib.h>
#include"Matrix.h"
 

int main(){
    
    Matrix A = newMatrix(3);
    Matrix B = newMatrix(3);
    Matrix C, D, E, F, G, H;

    changeEntry(A, 1,1,1.75);
    changeEntry(A, 1,2,2.53);
    changeEntry(A, 1,3,3.56);
    changeEntry(A, 2,1,4.53);
    changeEntry(A, 2,2,5.46);
    changeEntry(A, 2,3,6.96);
    changeEntry(A, 3,1,7.29);
    changeEntry(A, 3,2,8.93);
    changeEntry(A, 3,3,9.18);
 
    changeEntry(B, 1,1,1.78);
    changeEntry(B, 1,2,0);
    changeEntry(B, 1,3,1.35);
    changeEntry(B, 2,1,0);
    changeEntry(B, 2,2,1.73);
    changeEntry(B, 2,3,0);
    changeEntry(B, 3,1,7.29);
    changeEntry(B, 3,2,0);
    changeEntry(B, 3,3,8.18);
    
    C = copy(A);
    printf("nnz: %d\n", NNZ(C));
    printf("size: %d\n", size(C));
    printMatrix(stdout, C);
    printf("\n");
    printf("%s\n", equals(A, C)?"true":"false" );       //true
    
    D = sum(A, B);
    printf("nnz: %d\n", NNZ(D));
    printf("size: %d\n", size(D));
    printMatrix(stdout, D);
    printf("\n");
 
    E = diff(D, C);
    printf("nnz: %d\n", NNZ(E));
    printf("size: %d\n", size(E));
    printMatrix(stdout, E);
    printf("\n");
    
    F = transpose(B);
    printf("nnz: %d\n", NNZ(F));
    printf("size: %d\n", size(F));
    printMatrix(stdout, F);
    printf("\n");
 
    changeEntry(B, 3,3,0);
 
    G = product(B, F);
    printf("nnz: %d\n", NNZ(G));
    printf("size: %d\n", size(G));
    printMatrix(stdout, G);
    printf("\n");
    
    makeZero(G);
    printf("nnz: %d\n", NNZ(G));
    printf("size: %d\n", size(G));
    printMatrix(stdout, G);
    printf("\n");
 
    H = scalarMult(7.65, G);
    printf("nnz: %d\n", NNZ(H));
    printf("size: %d\n", size(G));
    printMatrix(stdout, H);
    printf("\n");
 

   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&C);
   freeMatrix(&D);
   freeMatrix(&E);
   freeMatrix(&F);
   freeMatrix(&G);
   freeMatrix(&H);

   return EXIT_SUCCESS;
}


