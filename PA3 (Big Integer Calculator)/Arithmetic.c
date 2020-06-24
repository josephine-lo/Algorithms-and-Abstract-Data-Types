/*--------------------------------------------------------------------------------------------
 * Josephine Lo, jowlo, 1689289
 * CSE101 - PA3
 * November 14th, 2019
 *--------------------------------------------------------------------------------------------
 * Arithmetic.c - A top level client file that opens an input file and writes to an output
 *  file that parses lines 2 & 4 as BigInteger A and BigInteger B, respectively. The output
 *  file prints A, B, A+B, A-B, A-A, 3A-2B, AB, A^2, B^2, 9*A^4+16*B^5
 *-------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "BigInteger.h"

#define MAX_LEN 100000

int main(int argc, const char * argv[]) {

    FILE *in, *out;
    char line1[MAX_LEN];
    char line2[MAX_LEN];
    int len1 = 0;
    int len2 = 0;
    
    if(argc != 3){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

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
     
    
    fscanf(in,"%d\n", &len1);
    int c = getc(in);
    if(c == '+' || c == '-' ){
        len1 = len1 + 1;
    }
    ungetc(c, in);
    fgets(line1, len1+1, in);

    fscanf(in,"%d\n", &len2);
    c = getc(in);
    if(c == '+' || c == '-' ){
        len2 = len2 + 1;
    }
    ungetc(c, in);
    fgets(line2, len2+1, in);    
    
    BigInteger A = stringToBigInteger(line1);
    BigInteger B = stringToBigInteger(line2);
    BigInteger C = stringToBigInteger("3");
    BigInteger D = stringToBigInteger("2");
    BigInteger E = stringToBigInteger("9");
    BigInteger F, G, H, I, J, K, M, N;
    BigInteger L = stringToBigInteger("16");
    
    //A
    printBigInteger(out, A);
    fprintf(out, "\n\n");

    //B
    printBigInteger(out, B);
    fprintf(out, "\n\n");
    
    //A+B
    F = sum(A, B);
    printBigInteger(out, F);
    fprintf(out, "\n\n");
    freeBigInteger(&F);

    //A-B
    G = diff(A, B);
    printBigInteger(out, G);
    fprintf(out, "\n\n");
    freeBigInteger(&G);

    //A-A
    H = diff(A, A);
    printBigInteger(out, H);
    fprintf(out, "\n\n");
    freeBigInteger(&H);    

    //3*A - 2*B
    I = prod(A, C);         // 3 * A
    J = prod(B, D);         // 2 * B
    K = diff(I, J);
    printBigInteger(out, K);
    fprintf(out, "\n\n");
    freeBigInteger(&I);
    freeBigInteger(&J);
    freeBigInteger(&K);

    //A*B
    F = prod(A, B);
    printBigInteger(out, F);
    fprintf(out, "\n\n");
    freeBigInteger(&F);

    //A*A
    F = prod(A, A);
    printBigInteger(out, F);
    fprintf(out, "\n\n");

    //B*B
    G = prod(B, B);
    printBigInteger(out, G);
    fprintf(out, "\n\n");

    // 9*A^4 + 16*B^5
    H = prod(F, F);         // A^4
    I = prod(H, E);         // A^4 * 9
    J = prod(G, G);         // B^4
    K = prod(J, B);         // B^5
    M = prod(K, L);         // B^5 * 16
    N = sum(I, M);
    printBigInteger(out, N);
    fprintf(out, "\n\n");
    
    
    freeBigInteger(&A);
    freeBigInteger(&B);
    freeBigInteger(&C);
    freeBigInteger(&D);
    freeBigInteger(&E);
    freeBigInteger(&F);
    freeBigInteger(&G);
    freeBigInteger(&H);
    freeBigInteger(&I);
    freeBigInteger(&J);
    freeBigInteger(&K);
    freeBigInteger(&L);
    freeBigInteger(&M);
    freeBigInteger(&N);
    fclose(in);
    fclose(out);

    return 0;
}

