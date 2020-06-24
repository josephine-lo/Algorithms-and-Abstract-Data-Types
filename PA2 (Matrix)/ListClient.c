
//-----------------------------------------------------------------------------
// ListClient.c
// Test client for List ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"List.h"

int notmain(int argc, char* argv[]){
   List A = newList();
   List B = newList();
   List C = newList();
   int cols[] = { 0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3 };
   double values[] = {0.0,1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9,10.10,11.11,12.12,13.13,14.14,15.15};
   int i, u=-1, v=-2, equal=0;

   // initialize Lists A and B
   for(i=0; i<16; i++){
	   Entry E = newEntry(cols[i], values[i]);
	   append(A, (void *) E);
	   prepend(B, (void *) E);
   }

   // print both lists of integers in forward direction
   for(moveFront(A); index(A)>=0; moveNext(A)){
	   printEntry(A);
   }
   printf("\n");
   for(moveFront(B); index(B)>=0; moveNext(B)){
	   printEntry(B);
   }
   printf("\n");

   // print both lists of integers in backward direction
   for(moveBack(A); index(A)>=0; movePrev(A)){
	   printEntry(A);
   }
   printf("\n");
   for(moveBack(B); index(B)>=0; movePrev(B)){
	   printEntry(B);
   }
   printf("\n");

   // make a shallow copy of A
   moveFront(A);
   while( index(A)>=0 ){
      append(C, get(A));
      moveNext(A);
   }
   // print the copy in forward direction
   for(moveFront(C); index(C)>=0; moveNext(C)){
	   printEntry(C);
   }
   printf("\n");

   // check shallow equality of A and C by comparing pointers
   equal = (length(A)==length(C));
   moveFront(A);
   moveFront(C);
   while( index(A)>=0 && equal){
      equal = ( get(A)==get(C) );
      moveNext(A);
      moveNext(C);
   }
   printf("A equals C is %s\n", (equal?"true":"false") );

   moveFront(A);
   for(i=0; i<5; i++) moveNext(A); // at index 5
   insertBefore(A, &u);            // now at index 6
   for(i=0; i<9; i++) moveNext(A); // at index 15
   insertAfter(A, &v);             // doesn't change index
   for(i=0; i<5; i++) movePrev(A); // at index 10
   delete(A);                      // index is now undefined

   // print A in forward and backward direction
   for(moveFront(A); index(A)>=0; moveNext(A)){
	   printEntry(A);
   }
   printf("\n");
   for(moveBack(A); index(A)>=0; movePrev(A)){
	   printEntry(A);
   }
   printf("\n");

   // check length of A, before and after clear()
   printf("%d\n", length(A));
   cclear(A);
   printf("%d\n", length(A));

   freeList(&A);
   freeList(&B);
   freeList(&C);

   return(0);
}

/*
Output of this program:
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
A equals C is true
1 2 3 4 5 -1 6 7 8 9 11 12 13 14 15 -2 16 17 18 19 20
20 19 18 17 16 -2 15 14 13 12 11 9 8 7 6 -1 5 4 3 2 1
21
0
*/

