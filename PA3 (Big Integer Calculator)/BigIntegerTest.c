/*--------------------------------------------------------------------------------------------
 * Josephine Lo, jowlo, 1689289
 * CSE101 - PA3
 * November 14th, 2019
 *--------------------------------------------------------------------------------------------
 * BigIntegerTest.c - Test file for the BigInteger ADT, where each List element is in 
 *  the range 0 <= x <= BASE, BASE = 10^POWER.
 *-------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "BigInteger.h"

int main(int argc, char* argv[]){

    char str[] = {"-1"};
    char str1[] = {"-100"};
    char str2[] = {"1"};
    char str3[] = {"100"};
    char str4[] = {"355797"};
    char str5[] = {"149082"};
    char str6[] = {"5555"};
    char str7[] = {"7402779357"};
    
    BigInteger A = stringToBigInteger(str);
    BigInteger B = stringToBigInteger(str1);
    BigInteger C = stringToBigInteger(str2);
    BigInteger D = stringToBigInteger(str3);
    BigInteger E;
    BigInteger F = stringToBigInteger(str4);
    BigInteger G = stringToBigInteger(str5);
    BigInteger H = stringToBigInteger(str6);
    BigInteger I = stringToBigInteger(str7);
    
    printf("compare: %d \n", compare(A,C));
    printf("equals: %d \n", equals(A,A));
    

    E = diff(A, D);     // -101
    printBigInteger(stdout, E);
    printf("\n");
    freeBigInteger(&E);
    E = sum(A, D);      //99
    printBigInteger(stdout, E);
    printf("\n");
    freeBigInteger(&E);
    E = diff(C, D);     //-99
    printBigInteger(stdout, E);
    printf("\n");
    freeBigInteger(&E);
    E = sum(A, B);      //-101
    printBigInteger(stdout, E);
    printf("\n");
    freeBigInteger(&E);
    E = diff(A, B);     //99
    printBigInteger(stdout, E);
    printf("\n");
    freeBigInteger(&E);
    E = sum(C, D);      //101
    printBigInteger(stdout, E);
    printf("\n");
    freeBigInteger(&E);
    E = diff(D, C);     //99
    printBigInteger(stdout, E);
    printf("\n");
    freeBigInteger(&E);
    E = sum(D, A);      //99
    printBigInteger(stdout, E);
    printf("\n");
    freeBigInteger(&E);
    E = diff(C, C);     //0
    printBigInteger(stdout, E);
    printf("\n");
    freeBigInteger(&E);
    E = sum(D, B);      //0
    printBigInteger(stdout, E);
    printf("\n");
    freeBigInteger(&E);
    E = sum(F, G);      //50 48 79
    printBigInteger(stdout, E);
    printf("\n");
    freeBigInteger(&E);
    E = diff(F, G);      //20 67 15
    printBigInteger(stdout, E);
    printf("\n");
    freeBigInteger(&E);
    
    E = prod(H, H);
    printBigInteger(stdout, E);
    printf("\n");
    freeBigInteger(&E);
    
    E = prod(I, I);
    printBigInteger(stdout, E);
    printf("\n");
    
    add(E, H, I);
    printf("sign: %d\n", sign(E));
    printBigInteger(stdout, E);
    printf("\n");
    freeBigInteger(&E);
    
    
    E = copy(D);
    negate(E);
    printf("sign: %d\n", sign(E));
    printBigInteger(stdout, E);
    printf("\n");
    freeBigInteger(&E);
    
    E = copy(A);
    subtract(E, H, I);
    printf("sign: %d\n", sign(E));
    printBigInteger(stdout, E);
    printf("\n");
    
    makeZero(E);
    multiply(E, H, I);
    printf("sign: %d\n", sign(E));
    printBigInteger(stdout, E);
    printf("\n");
    freeBigInteger(&E);
    

    printBigInteger(stdout, E);
    printf("\n");
    freeBigInteger(&E);
    
    
    freeBigInteger(&A);
    freeBigInteger(&B);
    freeBigInteger(&C);
    freeBigInteger(&D);
    freeBigInteger(&E);
    freeBigInteger(&F);
    freeBigInteger(&G);
    freeBigInteger(&H);
    freeBigInteger(&I);

    
    return 0;

}

