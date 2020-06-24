//-----------------------------------------------------------------------------
//  MatrixClient.c
//  A test client for the Matrix ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"Matrix.h"

int main1(){
   int n=3;
   Matrix A = newMatrix(n);
   Matrix B = newMatrix(n);
   Matrix C, D, E, F, G, H;

   changeEntry(A, 1,1,1); changeEntry(B, 1,1,1);
   changeEntry(A, 1,2,2); changeEntry(B, 1,2,0);
   changeEntry(A, 1,3,3); changeEntry(B, 1,3,1);
   changeEntry(A, 2,1,4); changeEntry(B, 2,1,0);
   changeEntry(A, 2,2,5); changeEntry(B, 2,2,1);
   changeEntry(A, 2,3,6); changeEntry(B, 2,3,0);
   changeEntry(A, 3,1,7); changeEntry(B, 3,1,1);
   changeEntry(A, 3,2,8); changeEntry(B, 3,2,1);
   changeEntry(A, 3,3,9); changeEntry(B, 3,3,1);
    
    printf("Matrix A ...\n");
    printMatrix(stdout, A);
    printf("\n");
    printf("Matrix B ...\n");
    printMatrix(stdout, B);
    printf("\n");

   printf("Number of non-zero entries: %d\n", NNZ(A));
   printMatrix(stdout, A);
   printf("\n");

   printf("Number of non-zero entries: %d\n", NNZ(B));
   printMatrix(stdout, B);
   printf("\n");

   C = scalarMult(1.5, A);
   printf("C =1.5A. Number of non-zero entries: %d\n", NNZ(C));
   printMatrix(stdout, C);
   printf("\n");

   D = sum(A, B);
   printf("D=A+B, Number of non-zero entries: %d\n", NNZ(D));
   printMatrix(stdout, D);
   printf("\n");

   E = diff(A, A);
   printf("E=A-A, Number of non-zero entries: %d\n", NNZ(E));
   printMatrix(stdout, E);
   printf("\n");

   F = transpose(B);
   printf("F=Bt, transpose. Number of non-zero entries: %d\n", NNZ(F));
   printMatrix(stdout, F);
   printf("\n");

   G = product(B, B);
   printf("G=B*B Number of non-zero entries: %d\n", NNZ(G));
   printMatrix(stdout, G);
   printf("\n");

   H = copy(A);
   printf("H=Copy A, Number of non-zero entries: %d\n", NNZ(H));
   printMatrix(stdout, H);
   printf("\n");

   printf("A=H? %s\n", equals(A, H)?"true":"false" );
   printf("A=B? %s\n", equals(A, B)?"true":"false" );
   printf("A=A? %s\n", equals(A, A)?"true":"false" );

   makeZero(A);
   printf("Zero A, %d\n", NNZ(A));
   printMatrix(stdout, A);

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


