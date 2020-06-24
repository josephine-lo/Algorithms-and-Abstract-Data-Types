/*--------------------------------------------------------------------------------------------
 * Josephine Lo, jowlo, 1689289
 * CSE101 - PA3
 * November 14th, 2019
 *--------------------------------------------------------------------------------------------
 * ListTest.c - Test file for the List ADT
 *-------------------------------------------------------------------------------------------*/

#include<stdio.h>
#include<stdlib.h>
#include"List.h"


int main(int argc, char* argv[]){
    
    List A = newList();
    List B = newList();
    List C = NULL;
    int i;
    
    for(i=1; i<=20; i++){
        append(A,i);
        prepend(B,i);
    }
    
    //printList(stdout,A);
    printf("\n");
    //printList(stdout,B);
    printf("\n");
     
    
    for(moveFront(A); index(A)>=0; moveNext(A)){
        printf("%ld ", get(A));
    }
    printf("\n");
    
    
    for(moveBack(B); index(B)>=0; movePrev(B)){
        printf("%ld ", get(B));

    }
    printf("\n");
    
    
    C = copyList(A);
    
    //printf("%s\n", equals(A,B)?"true":"false");
    //printf("%s\n", equals(B,C)?"true":"false");
    //printf("%s\n", equals(C,A)?"true":"false");
    
    
    moveFront(A);
    for(i=0; i<5; i++) moveNext(A); // at index 5
    insertBefore(A, -1);            // at index 6
    for(i=0; i<9; i++) moveNext(A); // at index 15
    insertAfter(A, -2);
    for(i=0; i<5; i++) movePrev(A); // at index 10

    delete(A);
    //printList(stdout,A);
    
    //start
    printf("\n");
    clear(A);
    append(A, 12);
    append(A, 123);
    append(A, 1234);
    append(A, 33333);
    append(A, 123456);
    append(A, 1234567);
    
    moveFront(A);
    for(i=0; i<3; i++) moveNext(A);
    set(A, 12345);
    //printList(stdout, A);
    
    for(moveBack(A); index(A)>=0; movePrev(A)){
        set(A, 222);
    }
    printf("\n");
    //printList(stdout,A);
    //end
    
    printf("\n");
    printf("%d\n", length(A));
    clear(A);
    printf("%d\n", length(A));
    
    freeList(&A);
    freeList(&B);
    freeList(&C);
    
    return(0);
}
 






