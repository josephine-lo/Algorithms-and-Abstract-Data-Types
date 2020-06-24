/*----------------------------------------------------------------------------
* Josephine Lo, jowlo, 1689289
* CSE101 - PA5
* December 6, 2019
* --------------------------------------------------------------------------
*  Graph.h - header file for the Graph ADT
* --------------------------------------------------------------------------*/

#ifndef Graph_h
#define Graph_h

#include <stdio.h>
#include "List.h"

#define NIL 0
#define UNDEF -1

#define WHITE 1
#define GRAY 2
#define BLACK 3

typedef struct GraphObj* Graph;

/* Constructors-Destructors */
Graph newGraph(int n);
void freeGraph(Graph* pG);
/* Access functions */
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
/* Manipulation procedures */
void addArc(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void addEdge(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void insertInPlace(List L, int v);
void DFS(Graph G, List S); /* Pre: length(S)==getOrder(G) */
void visit(Graph G, List S, int x, int* time);
/* Other Functions */
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out , Graph G);



#endif /* Graph_h */

