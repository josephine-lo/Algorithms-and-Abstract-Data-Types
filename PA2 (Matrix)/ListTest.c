
/*---------------------------------------------------------------------------------
 * Josephine Lo, jowlo, 1689289
 * CSE101 
 * October 29th, 2019
 *---------------------------------------------------------------------------------
 * ListTest.c - A test file to test the functions of the List ADT
 *--------------------------------------------------------------------------------*/

#include<stdio.h>
#include<stdlib.h>
#include"List.h"

int main(int argc, char* argv[]){
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
       Entry E = (Entry)get(A);
      printf("(%d, %2.2f) ", ((Entry)get(A))->column, ((Entry)get(A))->value);
      //(*(struct tDSA*)(parent->dynStructArray))->p1
   }
   printf("\n");
   for(moveFront(B); index(B)>=0; moveNext(B)){
       printf("(%d, %2.2f) ", ((Entry)get(B))->column, ((Entry)get(B))->value);
   }
   printf("\n");

   // print both lists of integers in backward direction
   for(moveBack(A); index(A)>=0; movePrev(A)){
       printf("(%d, %2.2f) ", ((Entry)get(A))->column, ((Entry)get(A))->value);
   }
   printf("\n");
   for(moveBack(B); index(B)>=0; movePrev(B)){
       printf("(%d, %2.2f) ", ((Entry)get(B))->column, ((Entry)get(B))->value);
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
       printf("(%d, %2.2f) ", ((Entry)get(C))->column, ((Entry)get(C))->value);
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
       printf("(%d, %2.2f) ", ((Entry)get(A))->column, ((Entry)get(A))->value);
   }
   printf("\n");
   for(moveBack(A); index(A)>=0; movePrev(A)){
       printf("(%d, %2.2f) ", ((Entry)get(A))->column, ((Entry)get(A))->value);
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




