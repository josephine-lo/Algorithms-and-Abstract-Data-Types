
/*---------------------------------------------------------------------------------
 * Josephine Lo, jowlo, 1689289
 * CSE101 
 * October 29th, 2019
 *---------------------------------------------------------------------------------
 * List.c - Implementation for the List ADT. Taken from PA1 with minor changes
 *--------------------------------------------------------------------------------*/

#include <stdlib.h>
#include <string.h>
#include "List.h"

// Entry Constructors-Destructors ---------------------------------------------------
typedef struct EntryObj { //equivalent to node
	int column;
	double value;
} EntryObj;

Entry newEntry(int col, double val) {
	Entry E = malloc(sizeof(EntryObj));
	E->column = col;
	E->value = val;
	return(E);
}

void freeEntry(Entry *pE) {
	if (pE != NULL && *pE != NULL) {
		free(*pE);
		*pE = NULL;
	}
}

// Entry manipulation functions
//void printEntry(FILE* out, List L) {
void printEntry(List L) {
		Entry E = (Entry)get(L);
	//printf("(%d, %f) ", (E)->column, (E)->value);
	if (E == NULL) {
		printf("Error: Entry is NULL!\n");
		return;
	}
	//fprintf(out, "(%d, %f) ", (E)->column, (E)->value);
	printf("(%d, %0.1f) ", (E)->column, (E)->value);
	//printf("(%d, %2.2f) ", ((Entry)get(L))->column, ((Entry)get(L))->value);
}
//print the contents of the Entry in (int, double) format

void chgEntry(List L, int col, double val) {
	for (moveFront(L); index(L) >= 0; moveNext(L)) {
		Entry E = (Entry)get(L);
		int col1 = (E)->column;
		if (col1 == col) {
			(E)->value = val;
			return;
		}
		else if (col1 > col) {
			Entry E1 = newEntry(col, val);
			insertBefore(L, (void *)E1);
			return;
		}
	}
	Entry E2 = newEntry(col, val);
	append(L, (void *)E2);
}
// change the value of the colummn if found, create a new Node with (col, value) otherwise.

int equalsEntry(Entry A, Entry B) {
	return (A->column == B->column && A->value == B->value);
}
// Returns true (1) iff Lists A and B are in same

int getEntryCol(List L) {
	Entry E = (Entry)get(L);
	if (E == NULL) {
		return 0;
	}
	return (E)->column;
}

double getEntryVal(List L) {
	Entry E = (Entry)get(L);
	if (E == NULL) {
		printf("List Error: invalid value in Entry\n");
        exit(EXIT_FAILURE);
	}
	return (E)->value;
}


typedef struct NodeObj{
    void* data;
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
Node newNode(void* data){
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->next = N->previous = NULL;
    return(N);
}

void freeNode(Node *pN){
    if(pN != NULL && *pN != NULL){
		freeEntry((Entry*)*pN);
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
    if (L == NULL){
        printf("List Error: calling length() on NULL List reference\n");
	exit(EXIT_FAILURE);
    } else {
        return L->length;
    }

} // Returns the number of elements in L.

int index(List L){
    if(L == NULL || L->cursor == NULL){
        return -1;
    }
    return L->index;
} // Returns index of cursor element if defined, -1 otherwise.

void* front(List L){
    if(L != NULL && length(L) > 0){
        return L->front->data;
    } else {
        return NULL;
    }

} // Returns front element of L. Pre: length()>0

void* back(List L){
    if(L != NULL && length(L) > 0){
        return L->back->data;
    }
    return NULL;
} // Returns back element of L. Pre: length()>0

void* get(List L){
    if(L != NULL && length(L) > 0){
        if(index(L) >= 0){
            return L->cursor->data;
        }
    }
    return NULL;
    
    
} // Returns cursor element of L. Pre: length()>0, index()>=0


int equalsList(List A, List B) {
	Node N = NULL;
	Node M = NULL;

    if (A == NULL || B == NULL) {
        printf("List Error: calling equals() on NULL List(s)");
        exit(EXIT_FAILURE);
    }
	else if (length(A) == 0 && length(B) == 0) {
		return 1;
	}
	else if (length(A) != length(B)) {
		return 0;
	}
	N = A->front;
	M = B->front;
	//List A & B have the same length
	int entryEqual = 0;
	while (N->next != NULL && M->next != NULL) {
		entryEqual = equalsEntry((Entry)N->data, (Entry)M->data);
		if (entryEqual) {
			N = N->next;
			M = M->next;
		}
		else {
			return 0;
		}
	}
	entryEqual = equalsEntry((Entry)N->data, (Entry)M->data);
	return entryEqual;
}
// Returns true (1) iff Lists A and B are in same


// Manipulation procedures ----------------------------------------------------
void clear(List L){
    Node N = L->front;
    while((L->length) > 0){
        Node M = N;
        N = N->next;
        freeNode(&M);
        L->length--;
    }

    L->front = L->back = L->cursor = NULL;
    L->index = -1;
} // Resets L to its original empty state.

void moveFront(List L){
    if(L != NULL){
        L->cursor = L->front;
        L->index = 0;
    }
} // If L is non-empty, sets cursor under the front element,
// otherwise does nothing.

void moveBack(List L){
    if(L != NULL){
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

void prepend(List L, void* data){
    Node N = newNode(data);
    if(L != NULL && length(L) != 0){
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


void append(List L, void* data){
    Node N = newNode(data);
    if(L != NULL && length(L) != 0){
        L->back->next = N;
        N->previous = L->back;
    } else {
        L->front = N;
    }
    L->back = N;
    L->length++;
    
} // Insert new element into L. If L is non-empty,
// insertion takes place after back element.

void insertBefore(List L, void* data){
    if(L == NULL || length(L) < 0 || index(L) < 0){
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

void insertAfter(List L, void* data){
    if(L == NULL || length(L) < 0 || index(L) < 0){
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
    if(L == NULL){
        printf("List Error: calling deleteFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(length(L) <= 0){
        printf("List Error: calling deleteFront() on empty List\n");
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
    if(L == NULL){
        printf("List Error: calling deleteBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(length(L) <= 0){
        printf("List Error: calling deleteBack() on empty List\n");
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
    if(L == NULL){
        printf("List Error: calling delete() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
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
void printList(FILE* out, List L) {
	if(out == NULL ){
		printf("List Error: calling printList() on NULL file reference\n");
		exit(EXIT_FAILURE);
    }
	Node N = NULL;
     
    for(N = L->front; N != NULL; N = N->next){
		Entry E = (Entry)N->data;
        double val = E->value;
        if (val != 0)
            fprintf(out, "(%d, %0.1f) ", E->column, val);
		//printf("(%d, %2.2f) ", E->column, E->value);
	}
 
 } // Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.


int isEmpty(List L){
    if(L == NULL){
        printf("List Error: calling isEmpty() on NULL List reference\n");
        exit(EXIT_FAILURE);
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


double getProdList(List L1, List L2){
    if (L1 == NULL || L2 == NULL)
        return 0;
    double p = 0;
    for (moveFront(L1), moveFront(L2); index(L1) >= 0 && index(L2) >= 0;){
        Entry E1 = (Entry)get(L1);
        int col1 = (E1)->column;
        Entry E2 = (Entry)get(L2);
        int col2 = (E2)->column;
        if (col1 == col2){
            p += (E1)->value * (E2)->value;
            moveNext(L1);
            moveNext(L2);
        } else if (col1 < col2){
            moveNext(L1);
        } else if (col1 > col2){
            moveNext(L2);
        }
    }
    return p;
} // Returns the product of the two lists: L1 and L2 as double.



