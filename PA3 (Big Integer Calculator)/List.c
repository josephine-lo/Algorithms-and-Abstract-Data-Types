/*--------------------------------------------------------------------------------------------
 * Josephine Lo, jowlo, 1689289
 * CSE101 - PA3
 * November 14th, 2019
* --------------------------------------------------------------------------
*  List.c - indirectly sorts the input file by creating a List and sorting
*      the indicies of the list in lexicographic ordering.
* --------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "List.h"

typedef struct NodeObj{
    long data;
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
Node newNode(long data){
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

long front(List L){
    if(length(L) > 0){
        return L->front->data;
    }
    return -1;
} // Returns front element of L. Pre: length()>0

long back(List L){
    if(length(L) > 0){
        return L->back->data;
    }
    return -1;
} // Returns back element of L. Pre: length()>0

long get(List L){
    if(length(L) > 0){
        if(index(L) >= 0){
            return L->cursor->data;
        }
    }
    return -1;
    
    
} // Returns cursor element of L. Pre: length()>0, index()>=0


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

void prepend(List L, long data){
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


void append(List L, long data){
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

void insertBefore(List L, long data){
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

void insertAfter(List L, long data){
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
        } else if(length(L) == 1){
            L->front = L->back = NULL;
        } else {
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
 void printList(FILE* out, List L, int BASE, int POWER, int sign){
     if(out == NULL){
         printf("Unable to open file for writing\n");
         exit(EXIT_FAILURE);
     }
     
     if(sign == -1){
         fprintf(out, "-");
     }
     
     moveBack(L);
     if(L->back != NULL){
         if(L->back->previous != NULL && L->back->data == 0){
             movePrev(L);
             
             if(L->back->previous == L->front){
                 fprintf(out, "%ld", L->back->previous->data);
                 movePrev(L);
             } else if(L->back->previous->data < BASE){
                 fprintf(out, "%ld", L->back->previous->data);
                 movePrev(L);
             }
         } else {
             fprintf(out, "%ld", L->back->data);
             movePrev(L);
         }
     }
     
     while(index(L) >= 0){
         if(L->cursor != NULL){
                 fprintf(out, "%0*ld", POWER, L->cursor->data);
         }
         movePrev(L);
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


long isEmpty(List L){
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


void set(List L, long x){
    if(length(L) <= 0){
        printf("List Error: calling set() on invalid List length\n");
        exit(EXIT_FAILURE);
    }
    if(L->index < 0){
        printf("List Error: calling set() on invalid List cursor index\n");
        exit(EXIT_FAILURE);
    }
    int n = 0;
    if(L->cursor == L->front){
        deleteFront(L);
        prepend(L, x);
        moveFront(L);
    } else if(L->cursor == L->back){
        deleteBack(L);
        append(L, x);
        moveBack(L);
    } else {    //cursor not at front or back
        insertBefore(L, x);
        movePrev(L);
        n = L->index;
        moveNext(L);
        delete(L);
        for(moveFront(L); index(L) != n; moveNext(L));
    }
}
// Overwrites the cursor element with x. Pre: length()>0, index()>=0


char* substr(const char *src, int m, int n){
    // get length of the destination string
    int len = n - m;

    // allocate (len + 1) chars for destination (+1 for extra null character)
    char *dest = (char*)malloc(sizeof(char) * (len + 1));

    // extracts characters between m'th and n'th index from source string
    // and copy them into the destination string
    for (int i = m; i < n && (*src != '\0'); i++)
    {
        *dest = *(src + i);
        dest++;
    }

    // null-terminate the destination string
    *dest = '\0';

    // return the destination string
    return dest - len;
}

List addNodes(List L, List L1, int BASE){
    long data, data1, sum, carry = 0;
    List L2 = newList();
    
    List *L3 = &L;
    List *L4 = &L1;
    
    if(L == NULL && L1 != NULL){
        L2 = copyList(L1);
        return L2;
    } else if(L1 == NULL && L != NULL){
        L2 = copyList(L);
        return L2;
    }
    
    if(length(L) < length(L1)){
        L3 = &L1;
        L4 = &L;
    }
    
    moveFront(L);
    moveFront(L1);
    while(index(*L3) >= 0){
        data = (*L3)->cursor->data;
        if((*L4)->cursor != NULL){
            data1 = (*L4)->cursor->data;
        } else {
            data1 = 0;
        }
        
        sum = data + data1;
        if(carry == 1){
            sum += 1;
            carry = 0;
        }
        
        if(sum >= BASE){
            sum -= (BASE);
            carry = 1;
        }
        
        append(L2, sum);
        sum = 0;
        data = 0;
        data1 = 0;
        moveNext(*(L3));
        moveNext(*(L4));
    }
    if(carry == 1){
        append(L2, 1);
    }
    
    return L2;
}

List subNodes(List L, List L1, int BASE){
    long data, data1, sum, carry = 0;
    List L2 = newList();
    
    List *L3 = &L;
    List *L4 = &L1;
    

    if(length(L) < length(L1)){
        L3 = &L1;
        L4 = &L;
    }
    
    moveFront(L);
    moveFront(L1);
    while(index(*L3) >= 0){
        data = (*L3)->cursor->data;
        if((*L4)->cursor != NULL){
            data1 = (*L4)->cursor->data;
        } else {
            data1 = 0;
        }
        
        sum = data - data1;
        if(carry == 1){
            sum -= 1;
            carry = 0;
        }
        
        if(sum < 0){
            sum += BASE;
            carry = 1;
        }
        
        //printf("sum: %ld\n", sum);
        append(L2, sum);
        sum = 0;
        data = 0;
        data1 = 0;
        moveNext(*(L3));
        moveNext(*(L4));
    }
    
    return L2;
}


void prodList(List pL, List aL, List bL, int BASE, int POWER){
    // Need to test if the aL & bL are of the same List
    // In such case, move the cursor will confuse the index.
    // Need to create a temp List and free it when done.
    int pIndex = -1, sameBigInt = 0;
    if (aL == bL) sameBigInt = 1;
    if (sameBigInt == 1) bL = copyList(aL);
    for (moveFront(aL); index(aL) >= 0; moveNext(aL)) {
        for (moveFront(bL); index(bL) >= 0; moveNext(bL)){
            long mydata = 0, carryOver = 0;
            mydata = aL->cursor->data * bL->cursor->data;
            carryOver = mydata / BASE;
            mydata %= BASE;
            pIndex = aL->index + bL->index;
            makingPlist(pL, mydata, pIndex, BASE);
            if (carryOver > 0)
                makingPlist(pL, carryOver, pIndex + 1, BASE);
        }
    }
    if (sameBigInt == 1) freeList(&bL);
}

void makingPlist(List pL, long data, int pIndex, int BASE){
    // if the location seeking for is larger than (length - 1),
    // the Node does not exist.
    if (pIndex > pL->length - 1){
        append(pL, data);
    } else {
        // seeking the correct location to add in the value
        for (moveFront(pL); index(pL) < pIndex;)
            moveNext(pL);
        pL->cursor->data += data;
        long mydata = 0, carryOver = 0;
        mydata = pL->cursor->data;
        carryOver = mydata / BASE;
        if (carryOver > 0) {
            mydata %= BASE;
            pL->cursor->data = mydata;
            makingPlist(pL, carryOver, pIndex + 1, BASE);
        }
    }
}


// -1: L1 < L2, 1: L1 > L2, 0: L1 = L2.
int compareNodes(List L1, List L2){
    int len1 = 0;
    int len2 = 0;
    if(L1 != NULL && L2 != NULL){
        len1 = length(L1);
        len2 = length(L2);
    }
    int compare = 0;
    int c = 0;
    
    if(len1 > len2){
        return 1;
    } else if(len2 > len1){
        return -1;
    } else {    //len1 == len2
        moveBack(L1);
        moveBack(L2);
        
        while(index(L1) >= 0){
            if(L1->cursor != NULL && L2->cursor != NULL){
                
                if(L1->cursor->data == L2->cursor->data){
                    if(L1->cursor->previous == NULL){   //reach end
                        compare = 1;
                        break;
                    }
                    movePrev(L1);
                    movePrev(L2);
                } else {
                    compare = 1;
                    break;
                }
                
            } else {
                compare = 1;
                break;
            }
        }
    }
    
    if(compare == 1){
        if(L1->cursor->data > L2->cursor->data){
            c = 1;
        } else if(L1->cursor->data < L2->cursor->data){
            c = -1;
        } else {
            c = 0;
        }
        return c;
    }
    return c;
}

