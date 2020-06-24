/*----------------------------------------------------------------------------
* Josephine Lo, jowlo, 1689289
* CSE101 - PA5
* December 6, 2019
* --------------------------------------------------------------------------
*  Graph.c - implementation file for the Graph ADT that uses DFS to find
*       the strongly components of a diagraph
* --------------------------------------------------------------------------*/
#include "Graph.h"
#include "List.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct GraphObj{
    List* adj;
    int* color;
    int* discTime;
    int* finTime;
    int* parent;
    
    int order;      // # of vertices
    int size;       // # of edges

} GraphObj;

/* Constructors-Destructors */
Graph newGraph(int n){
    Graph G = malloc(sizeof(GraphObj));
    G->adj = malloc((n+1) * sizeof(List));
    G->color = malloc((n+1) * sizeof(int));
    G->discTime = malloc((n+1) * sizeof(int));
    G->finTime = malloc((n+1) * sizeof(int));
    G->parent = malloc((n+1) * sizeof(int));
    
    for(int i = 1; i < n+1; i++){
        G->adj[i] = newList();
        G->color[i] = WHITE;
        G->discTime[i] = UNDEF;
        G->finTime[i] = UNDEF;
        G->parent[i] = NIL;
    }
    G->order = n;
    G->size = 0;

    return G;
}

void freeGraph(Graph* pG){
    Graph G = *pG;
    int *colorArr = G->color;
    int *discTimeArr = G->discTime;
    int *finTimeArr = G->finTime;
    int *parentArr = G->parent;
    for(int i = 1; i < G->order+1; i++){
        freeList(&(G->adj[i]));
    }
    free(colorArr);
    free(discTimeArr);
    free(finTimeArr);
    free(parentArr);
    free(G->adj);
    G->adj = NULL;
    free(*pG);
    pG = NULL;
}

/* Access functions */
// getOrder() - returns the number of vertices in G
int getOrder(Graph G){
    if(G == NULL){
        printf("Graph Error: calling getOrder() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->order;
}

// getSize() = returns the size of G
int getSize(Graph G){
    if(G == NULL){
        printf("Graph Error: calling getSize() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->size;
}

// getParent() - return the appropriate field values for the given vertex
//      parent of a vertex may be NIL
// Pre: 1<=u<=n=getOrder(G)
int getParent(Graph G, int u){
    if(G == NULL){
        printf("Graph Error: calling getParent() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if(u < 1 || u > getOrder(G)){
        return NIL;
    }
    return G->parent[u];
}

// getDiscover() - return the appropriate field values for the given vertex
// Pre: 1<=u<=n=getOrder(G)
int getDiscover(Graph G, int u){
    if(G == NULL){
        printf("Graph Error: calling getDiscover() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if(u < 1 || u > getOrder(G)){
        return UNDEF;
    }
    return G->discTime[u];
}

// getFinish() - return the appropriate field values for the given vertex
// Pre: 1<=u<=n=getOrder(G)
int getFinish(Graph G, int u){
    if(G == NULL){
        printf("Graph Error: calling getFinish() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if(u < 1 || u > getOrder(G)){
        return UNDEF;
    }
    return G->finTime[u];
}

/* Manipulation procedures */
// addArc() - inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u (but not u to the adjacency List of v).
// Pre: 1 <= u <= getOrder(G), 1 <= v <= getOrder(G)
void addArc(Graph G, int u, int v){
    if(G == NULL){
        printf("Graph Error: calling addArc() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
        printf("Graph Error: calling addArc() with invalid value\n");
        exit(EXIT_FAILURE);
    }

    insertInPlace(G->adj[u], v);
    G->size++;
}

// addEdge() - inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v to the adjacency List of u.
// Pre: 1 <= u <= getOrder(G), 1 <= v <= getOrder(G)

void addEdge(Graph G, int u, int v){
    if(G == NULL){
        printf("Graph Error: calling addEdge() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
        printf("Graph Error: calling addEdge() with invalid value\n");
        exit(EXIT_FAILURE);
    }
    insertInPlace(G->adj[u], v);
    insertInPlace(G->adj[v], u);
    G->size++;
}

//insertInPlace() - helper function based on insertion sort that inserts v in the correct place
void insertInPlace(List L, int v){
    int key = 0;
    moveFront(L);
    for(int i = 0; i < length(L); i++){
        key = get(L);
        if (v < key){
            insertBefore(L, v);
            break;
        }
        moveNext(L);
    }
    if(index(L) == -1){
        append(L, v);
    }
    //printList(stdout, L);
}

// Pre: length(𝑆) == getOrder(G)
void DFS(Graph G, List S){
    if(length(S) != getOrder(G)){
        printf("Graph Error: calling DFS() with invalid length\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 1; i < getOrder(G)+1; i++){
        G->color[i] = WHITE;
        G->parent[i] = NIL;
    }
    int time = 0;
    moveFront(S);
    for(int u = 1; u < getOrder(G)+1; u++){
        if(G->color[get(S)] == WHITE){
            visit(G, S, get(S), &time);
        }
        moveNext(S);
    }
    
    for(int u = 1; u < getOrder(G)+1; u++){
        deleteBack(S);
    }
}

void visit(Graph G, List S, int u, int* time){
    *time = *(time) + 1;
    G->discTime[u] = *time;
    G->color[u] = GRAY;
    moveFront(G->adj[u]);
    while(index(G->adj[u]) != -1){
        int v = get(G->adj[u]);
        if(G->color[v] == WHITE){
            G->parent[v] = u;
            visit(G, S, v, time);
        }
        moveNext(G->adj[u]);
    }
    G->color[u] = BLACK;
    *time = *(time) + 1;
    G->finTime[u] = *time;
    prepend(S, u);
}

/* Other Functions */
// transpose() - returns a reference to a new graph object representing the transpose of G
Graph transpose(Graph G){
    Graph H = newGraph(G->order);
    
    for(int i = 1; i < G->order+1; i++){
        moveFront(G->adj[i]);
        while(index(G->adj[i]) != -1){
            append(H->adj[get(G->adj[i])], i);
            moveNext(G->adj[i]);
        }
    }
    return H;
}

// copyGraph() - returns a reference to a new graph which is a copy of G
Graph copyGraph(Graph G){
    Graph copyG = newGraph(G->order);
    for(int i = 1; i < getOrder(G)+1; i++){
        moveFront(G->adj[i]);
        while(index(G->adj[i]) != -1){
            append(copyG->adj[i], get(G->adj[i]));
            moveNext(G->adj[i]);
        }
        copyG->color[i] = G->color[i];
        copyG->discTime[i] = G->discTime[i];
        copyG->finTime[i] = G->finTime[i];
        copyG->parent[i] = G->parent[i];
    }
    return copyG;
}

// printGraph() - prints the adjacency list representation of G to the file pointed to by out
void printGraph(FILE* out , Graph G){
    for(int i = 1; i < getOrder(G)+1; i++){
      fprintf(out, "%d: ", i);
      printList(out, G->adj[i]);
      fprintf(out, "\n");
    }
}

