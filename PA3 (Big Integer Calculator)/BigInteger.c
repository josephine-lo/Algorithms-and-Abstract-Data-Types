/*--------------------------------------------------------------------------------------------
 * Josephine Lo, jowlo, 1689289
 * CSE101 - PA3
 * November 14th, 2019
 *--------------------------------------------------------------------------------------------
 * BigInteger.c - Implementation file for the BigInteger ADT, where each List element is in 
 *  the range 0 <= x <= BASE, BASE = 10^POWER.
 *-------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "BigInteger.h"
#include "List.h"


#define BASE 1000000000
#define POWER 9

// Exported type -------------------------------------------------------------
typedef struct BigIntegerObj{
    int sign;
    List L;
} BigIntegerObj;

// BigInteger reference type
typedef struct BigIntegerObj* BigInteger;

// Constructors-Destructors ---------------------------------------------------
// newBigInteger()
// Returns a reference to a new BigInteger object in the zero state.
BigInteger newBigInteger(){
    BigInteger B = malloc(sizeof(BigIntegerObj));
    B->sign = 0;
    B->L = newList();
    return B;
}
// freeBigInteger()
// Frees heap memory associated with *pB, sets *pB to NULL.
void freeBigInteger(BigInteger* pB){
    if(pB == NULL){
        printf("Big Integer Error: calling freeBigInteger() on NULL pointer reference\n");
        exit(EXIT_FAILURE);
    }
    BigInteger B = *pB;
    if(pB != NULL && *pB != NULL){
        freeList(&(B->L));
        free(*pB);
        *pB = NULL;
        pB = NULL;
    }
    
}
// Access functions -----------------------------------------------------------
// sign()
// Returns -1 if B is negative, 1 if B is positive, and 0 if B is in the zero
// state.
int sign(BigInteger B){
    if(B->sign == 0){
        return 0;
    } else if(B->sign > 0){
        return 1;
    } else {
        return -1;
    }
}

// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
int compare(BigInteger A, BigInteger B){
    int c = compareNodes(A->L, B->L);
    return c;
}

// equals()
// Return true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B){
    int c = compareNodes(A->L, B->L);
    if(c == 0 && A->sign == B->sign){
        return 1;
    } else {
        return 0;
    }
}

// Manipulation procedures ----------------------------------------------------

// makeZero()
// Re-sets B to the zero state.
void makeZero(BigInteger B){
    B->sign = 0;
    if(B->L != NULL){
        freeList(&(B->L));
    }
    B->L = newList();
}


// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the
// zero state.
void negate(BigInteger B){
    if(B->sign > 0){
        B->sign = -1;
    }else if(B->sign < 0){
        B->sign = 1;
    }
}

// BigInteger Arithmetic operations -----------------------------------------------
// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer
// represented in base 10 by the string s.
// Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9}
// and an optional sign {+, -} prefix.
BigInteger stringToBigInteger(char* s){
//    int minIndex = 0;
    if(s == NULL){
        printf("BigInteger Error: calling stringToBigInteger() with NULL string reference\n");
        exit(EXIT_FAILURE);
    }
    if(strlen(s) == 0){
        printf("BigInteger Error: calling stringToBigInteger() with empty string reference\n");
        exit(EXIT_FAILURE);
    }
    if(!isdigit(s[0]) && (s[0] != '+' && s[0] != '-')){
        printf("BigInteger Error: calling stringToBigInteger() without all base ten digits reference\n");
        exit(EXIT_FAILURE);
    }
    if(strlen(s) > 0){
        for(int i = 1; i < strlen(s)-1; i++){
            if(!isdigit(s[i])){
                printf("BigInteger Error: calling stringToBigInteger() without all base ten digits reference\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    int flag = 0;       //0 - no sign in front, 1 - sign in front
    BigInteger B = newBigInteger();
    B->sign = 1;
    long data = 0;
    
    if(s[0] == '+'){
        flag = 1;
        B->sign = 1;
    } else if(s[0] == '-'){
        flag = 1;
        B->sign = -1;
    }
    
    char* ss;
    if (flag ==1){
        ss = &s[1];
    } else {
        ss = s;
    }
    int length = (int) strlen(ss);

    int r = 0;
    r = length % POWER;
    
    char* dest;

    for(int i = length - 1; i >= r; i -= POWER){
        dest = substr(ss, i-POWER+1, i+1);
        data = (long) atoi(dest);
        append(B->L, data);
        free(dest);
        //printf("%s\n", dest);
    }
    
    //dealing with the remainder
    if(r != 0){
        dest = substr(ss, 0, r);
        data = (long) atoi(dest);
        append(B->L, data);
        free(dest);
        //printf("%s\n", dest);
    }
    return B;
}

// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N){
    BigInteger B = newBigInteger();
    freeList(&(B->L));
    B->sign = N->sign;
    if(N->L != NULL){
        B->L = copyList(N->L);
        freeList(&(N->L));
    }
    return B;
}

// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its
// current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B){
    freeList(&(S->L));
    BigInteger S1 = NULL;
    S1 = sum(A, B);
    S->L = copyList(S1->L);
    S->sign = S1->sign;
    freeBigInteger(&S1);
}

// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B){
    BigInteger S = newBigInteger();
    freeList(&(S->L));
    List L1 = NULL;
    int c = 0;
    
    c = compare(A, B);
    if(A->sign == 1){
        if(B->sign != -1){
            S->sign = 1;
            L1 = addNodes(A->L, B->L, BASE);
        } else {
            if(c == 0){
                S->sign = 0;
            } else if(c == 1){
                S->sign = 1;
            } else {
                S->sign = -1;
            }
            L1 = subNodes(A->L, B->L, BASE);
        }
    } else if(A->sign == 0){
        if(B->sign == 1 || B->sign == -1){
            S->sign = B->sign;
        } else {    // B->sign == 0
            S->sign = 0;
        }
        L1 = addNodes(A->L, B->L, BASE);
    } else {    // A->sign = -1
        if(B->sign == -1 || B->sign == 0){
            S->sign = -1;
            L1 = addNodes(A->L, B->L, BASE);
        } else {    // B->sign == 1
            if(c == 1){ // A > B
                S->sign = -1;
                L1 = subNodes(A->L, B->L, BASE);
            } else if(c == -1){  // A < B
                S->sign = 1;
                L1 = subNodes(B->L, A->L, BASE);
            } else {
                S->sign = 0;
                S->L = newList();
                append(S->L, 0);
                return S;
            }
        }
    }
    
    S->L = L1;
    return S;
}

// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting
// its current state: D = A - B
void subtract(BigInteger D, BigInteger A, BigInteger B){
    freeList(&(D->L));
    BigInteger D1 = NULL;
    D1 = diff(A, B);
    D->L = copyList(D1->L);
    D->sign = D1->sign;
    freeBigInteger(&D1);
}
// diff()
// Returns a reference to a new BigInteger object representing A - B.
BigInteger diff(BigInteger A, BigInteger B){
    BigInteger D = newBigInteger();
    freeList(&(D->L));
    List L1 = NULL;
    int c = 0;

    c = compare(A, B);
    
    if(c == 1){     // A > B
        if(B->sign != -1){
            if(A->sign == 1){
                D->sign = 1;
            } else { //A->sign is 0 or -1
                D->sign = -1;
            }
            L1 = subNodes(A->L, B->L, BASE);
        } else {    // B->sign == -1
            if(A->sign == 1){
                D->sign = 1;
                L1 = addNodes(A->L, B->L, BASE);
            } else if(A->sign == -1){ //A->sign is -1
                D->sign = -1;
                L1 = subNodes(B->L, A->L, BASE);
            } else {    // A->sign is 0
                D->sign = 1;
                L1 = addNodes(A->L, B->L, BASE);
            }
        }
    } else if(c == -1){ // B > A
        if(A->sign != -1){
            if(B->sign == 1){
                D->sign = -1;
            } else if(B->sign != 1){ //B->sign is 0 or -1
                D->sign = -1;
            }
            L1 = subNodes(B->L, A->L, BASE);
        } else {    // A->sign == -1
            if(B->sign == 1){
                D->sign = -1;
                L1 = addNodes(A->L, B->L, BASE);
            } else if(B->sign == -1){ //A->sign is -1
                D->sign = 1;
                L1 = subNodes(B->L, A->L, BASE);
            } else {    // A->sign is 0
                D->sign = 1;
                L1 = addNodes(B->L, A->L, BASE);
            }
        }
    } else {  
        D->sign = 0;
        D->L = newList();
        append(D->L, 0);
        return D;
    }
    D->L = L1;
    return D;
}


// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting
// its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B){
    freeList(&(P->L));
    BigInteger P1 = NULL;
    P1 = prod(A, B);
    P->L = copyList(P1->L);
    P->sign = P1->sign;
    freeBigInteger(&P1);
}
// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B){
    BigInteger P = newBigInteger();
    int signA = A->sign;
    int signB = B->sign;
    if (signA == 0) signA = 1;
    if (signB == 0) signB = 1;
    P->sign = signA * signB;
    prodList(P->L, A->L, B->L, BASE, POWER);
    
    return P;
}
// Other operations -----------------------------------------------------------
// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE* out, BigInteger B){
    if(out == NULL){
        printf("BigInteger Error: calling printBigInteger() on NULL file reference\n");
        exit(EXIT_FAILURE);
    }
    if(B != NULL){
        if(B->L != NULL){
            printList(out, B->L, BASE, POWER, B->sign);
            printf("\n\n");
        }

    }
}

