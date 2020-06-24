
/*----------------------------------------------------------------------------------
 * Josephine Lo, 1689289, jowlo
 * CSE101 - PA4
 * November 29th, 2019
 *----------------------------------------------------------------------------------
 * List.c - Implementation of a doubly linked list
 *----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

typedef struct NodeObj{
    int data;
    struct NodeObj* previous;
    struct NodeObj* next;
} NodeObj;


typedef NodeObj* Node;

typedef struct ListObj{
    Node front;
    Node back;
    Node cursor;
    int length;
    int index;
} ListObj;


// Constructors-Destructors ---------------------------------------------------
Node newNode(int data){
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->next = N->previous = NULL;
    return(N);
}

void freeNode(Node *pN){
    if(pN != NULL && *pN != NULL){
        free(*pN);
        *pN = NULL;
    }
}

List newList(void){
    List L;
    L = malloc(sizeof(ListObj));
    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->index = -1;
    return(L);
    
} // Creates and returns a new empty List.

void freeList(List* pL){
    if(pL != NULL && *pL != NULL){
        while (!isEmpty(*pL)){
            deleteBack(*pL);
        }
        free(*pL);
        *pL = NULL;
    }
} // Frees all heap memory associated with *pL, and sets
// *pL to NULL.

// Access functions -----------------------------------------------------------
int length(List L){
    return L->length;
} // Returns the number of elements in L.

int index(List L){
    //int i = 0;
    //Node N = NULL;
    if(L->cursor == NULL){  //problem
        return -1;
    }
    
    return L->index;
} // Returns index of cursor element if defined, -1 otherwise.

int front(List L){
    if(length(L) > 0){
        return L->front->data;
    }
    return -1;
} // Returns front element of L. Pre: length()>0

int back(List L){
    if(length(L) > 0){
        return L->back->data;
    }
    return -1;
} // Returns back element of L. Pre: length()>0

int get(List L){
    if(length(L) > 0){
        if(index(L) >= 0){
            return L->cursor->data;
        }
    }
    return -1;
    
    
} // Returns cursor element of L. Pre: length()>0, index()>=0


int equals(List A, List B){
    Node N = NULL;
    Node M = NULL;
    int eq = 0;

    if(length(A) == 0 && length(B) == 0){
        eq = 1;
        return eq;
    } else if(A == NULL || B == NULL){
        printf("List Error: calling equals() on NULL List(s)");
        exit(EXIT_FAILURE);
    } else if(length(A) != length(B)){
        return 0;
    }
    N = A->front;
    M = B->front;

    while(N->next != NULL && M->next != NULL){
        if(N->data == M->data){
            eq = 1;
            N = N->next;
            M = M->next;
        } else {
            eq = 0;
            return eq;
        }
    }
    if(N->data == M->data){
            eq = 1;
        } else {
            eq = 0;
        }

    return eq;
}

// Returns true (1) iff Lists A and B are in same
// state, and returns false (0) otherwise.
// Manipulation procedures ----------------------------------------------------
void clear(List L){
    Node N = L->front;
    while(N != NULL){
        Node M = N;
        N = N->next;
        freeNode(&M);
    }

    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->index = -1;
} // Resets L to its original empty state.

void moveFront(List L){
    if(L->length > 0){
        L->cursor = L->front;
        L->index = 0;
    }
} // If L is non-empty, sets cursor under the front element,
// otherwise does nothing.

void moveBack(List L){
    if(L->length > 0){
        L->cursor = L->back;
        L->index = length(L) - 1;
    }
} // If L is non-empty, sets cursor under the back element,
// otherwise does nothing.

void movePrev(List L){
    Node N = L->cursor;
    if(L->cursor != NULL){
        if(L->cursor != L->front){
            L->cursor = N->previous;
            L->index--;
        } else if(L->cursor == L->front) {
            L->cursor = NULL;
            L->index = -1;
        }
    }
    
} // If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing

void moveNext(List L){
    Node N = L->cursor;
    if(L->cursor != NULL){
        if(L->cursor != L->back){
            L->cursor = N->next;
        } else if(L->cursor == L->back) {
            L->cursor = NULL;
        }
    }
    L->index++;
    
} // If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing

void prepend(List L, int data){
    Node N = newNode(data);
    if(length(L) != 0){
        N->next = L->front;
        L->front->previous = N;
    
    } else {
        L->back = N;
    }
    
    if(index(L) != -1){
        L->index++;
    }
    L->front = N;
    L->length++;
    
    
} // Insert new element into L. If L is non-empty,
// insertion takes place before front element.


void append(List L, int data){
    Node N = newNode(data);
    if(length(L) != 0){
        L->back->next = N;
        N->previous = L->back;
    } else {
        L->front = N;
    }
    L->back = N;
    L->length++;
    
} // Insert new element into L. If L is non-empty,
// insertion takes place after back element.

void insertBefore(List L, int data){
    if(length(L) < 0 || index(L) < 0){
        printf("List Error: calling insertBefore() on empty List\n");
        exit(EXIT_FAILURE);
    }
    if(L->cursor == NULL){
        printf("List Error: calling insertBefore() on List with NULL cursor\n");
        exit(EXIT_FAILURE);
    }
    
    Node N = newNode(data);
    if(length(L) >= 1){
        if(L->cursor != L->front){
            N->previous = L->cursor->previous;
            L->cursor->previous->next = N;
        } else {
            L->front = N;
        }
        L->index++;
    }
    N->next = L->cursor;
    L->cursor->previous = N;

    L->length++;
    
} // Insert new element before cursor.
// Pre: length()>0, index()>=0

void insertAfter(List L, int data){
    if(length(L) < 0 || index(L) < 0){
        printf("List Error: calling insertAfter() on empty List\n");
        exit(EXIT_FAILURE);
    }
    if(L->cursor == NULL){
        printf("List Error: calling insertAfter() on List with NULL cursor\n");
        exit(EXIT_FAILURE);
    }
    Node N = newNode(data);
    if(length(L) >= 1){
        if(L->cursor != L->back){
            N->next = L->cursor->next;
            L->cursor->next->previous = N;
        } else {
            N->next = NULL;
            L->back = N;
        }
    }
    N->previous = L->cursor;
    L->cursor->next = N;
    
    L->length++;
    
    
} // Insert new element after cursor.
// Pre: length()>0, index()>=0

void deleteFront(List L){
    if(length(L) <= 0){
        printf("List Error: calling deleteFront() on empty List\n");
    }
    if(L == NULL){
        printf("List Error: calling deleteFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    Node N = L->front;
    
    if(L->cursor == L->front){
        L->index = -1;
    } else {
        L->index--;
    }
    
    if(length(L) > 1){
        L->front = L->front->next;
    } else {    //length == 1
        L->front = L->back = NULL;
    }
    
    L->length--;
    freeNode(&N);
} // Delete the front element. Pre: length()>0

void deleteBack(List L){
    if(length(L) <= 0){
        printf("List Error: calling deleteBack() on empty List\n");
        exit(EXIT_FAILURE);
    }
    if(L == NULL){
        printf("List Error: calling deleteBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->cursor == L->back){
        L->index = -1;
    }
    Node N = L->back;
    if(length(L) > 1){
        L->back = L->back->previous;
        L->back->next = NULL;
    } else {    //length == 1
        L->front = L->back = NULL;
    }
    L->length--;
    freeNode(&N);
    
} // Delete the back element. Pre: length()>0


void delete(List L){
    if(length(L) <= 0){
        printf("List Error: calling delete() on empty List\n");
        exit(EXIT_FAILURE);
    }
    if(index(L) < 0){
        printf("List Error: calling delete() on invalid index\n");
        exit(EXIT_FAILURE);
    }
    Node N = L->cursor;
    if(length(L) >= 1){
        if(N == L->front){
            L->front = L->front->next;
        } else if(N == L->back){
            L->back = L->back->previous;
            L->back->next = NULL;
        } else if(length(L) == 1){
            L->front = L->back = NULL;
        } else { //length > 1
            N->previous->next = N->next;
            N->next->previous = N->previous;
        }
    }
    freeNode(&N);
    L->cursor = NULL;
    L->index = -1;
    L->length--;
    
} // Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0


// Other operations -----------------------------------------------------------
 void printList(FILE* out, List L){
     if(out == NULL ){
         printf("Unable to open file for writing\n");
         exit(1);
     }
     Node N = NULL;
     
     for(N = L->front; N != NULL; N = N->next){
         fprintf(out, "%d ", N->data);
     }
 
 } // Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.


 List copyList(List L){
     List L1 = newList();
     Node N = NULL;

     for(N = L->front; N != NULL; N = N->next){
         append(L1, N->data);
     }
     
     
    return L1;
} // Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.


int isEmpty(List L){
    if(L == NULL){
        printf("List Error: calling isEmpty() on NULL List reference\n");
        exit(1);
    }
    return (L->length == 0);
}

List concatList(List A, List B){
    List L1 = newList();
    Node N = A->front;
    Node M = B->front;
    while(N != NULL){
        append(L1, N->data);
        N = N->next;
    }
    while(M != NULL){
        append(L1, M->data);
        M = M->next;
    }
    return L1;
} // Returns a new List which is the concatenation of
// A and B. The cursor in the new List is undefined,
// regardless of the states of the cursors in A and B.
// The states of A and B are unchanged.

