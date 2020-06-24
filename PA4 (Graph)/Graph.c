/*----------------------------------------------------------------------------------
 * Josephine Lo, 1689289, jowlo
 * CSE101 - PA4
 * November 29th, 2019
 *----------------------------------------------------------------------------------
 * Graph.c - A representation of a graph as an array of Lists and contains algorithms
 *      such as Breadth Fist Search (BFS) where each graph has a color (color[v]),
 *      parent (parent[v]), or distance (dist[v])
 *----------------------------------------------------------------------------------*/

#include "Graph.h"
#include "List.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct GraphObj{
    List* adj;
    int* color;
    int* parent;
    int* dist;
    
    int order;      // # of vertices
    int size;       // # of edges
    int source;
} GraphObj;


/*** Constructors-Destructors ***/
// newGraph() - returns a Graph pointing to a newly created GraphObj representing graph having n vertices and no edges
Graph newGraph(int n){
    Graph G = malloc(sizeof(GraphObj));
    G->adj = malloc((n+1) * sizeof(List));
    G->color = malloc((n+1) * sizeof(int));
    G->parent = malloc((n+1) * sizeof(int));
    G->dist = malloc((n+1) * sizeof(int));
    
    for(int i = 1; i < n+1; i++){
        G->adj[i] = newList();
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->dist[i] = INF;
    }
    G->order = n;
    G->size = 0;
    G->source = NIL;
    

    return G;
}

// freeGraph() - frees all dynamic memory associated with the Graph *pG, then sets the handle *pG to NULL.
void freeGraph(Graph* pG){
    Graph G = *pG;
    int *colorArr = G->color;
    int *distArr = G->dist;
    int *parentArr = G->parent;
    for(int i = 1; i < G->order+1; i++){
        freeList(&(G->adj[i]));
    }
    free(colorArr);
    free(distArr);
    free(parentArr);
    free(G->adj);
    G->adj = NULL;
    free(*pG);
    pG = NULL;
}


/*** Access functions ***/
// getOrder() - return order (# of vertices)
int getOrder(Graph G){
    if(G == NULL){
        printf("Graph Error: calling getOrder() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->order;
}

// getSize() - return size (# of edges)
int getSize(Graph G){
    if(G == NULL){
        printf("Graph Error: calling getSize() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->size;
}

// getSource() - returns the source vertex most recently used in function BFS(), or NIL if BFS() has not yet been called
int getSource(Graph G){
    if(G != NULL){
        return G->source;
    } else {
        return NIL;
    }
}

// getParent() - will return the parent of vertex u in the BreadthFirst tree created by BFS(), or NIL if BFS() has not yet been called.
// Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u){
    if(G == NULL){
        printf("Graph Error: calling getParent() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if(u < 1 || u > getOrder(G)){
        return NIL;
    } else {
        return G->parent[u];
    }
}

// getDist() - returns the distance from the most recent BFS source to vertex u, or INF if BFS() has not yet been called
// Pre: 1 <= u <= getOrder(G)
int getDist(Graph G, int u){
    if(G == NULL){
        printf("Graph Error: calling getDist() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if(u < 1 || u > getOrder(G)){
        return INF;
    } else {
        return G->dist[u];
    }
}

// getPath() - appends to the List L the vertices of a shortest path in G from source to u, or appends to L the value NIL if no such path exists
// Pre: getSource(G)!=NIL, so BFS() must be called before getPath().
// Pre: 1 <= u <= getOrder(G)
void getPath(List L, Graph G, int u){
    if(G == NULL){
        printf("Graph Error: calling getPath() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if(u < 1 || u > getOrder(G)){
        printf("Graph Error: calling getPath() with invalid value\n");
        exit(EXIT_FAILURE);
    }
    if(u == G->source){
        append(L, u);
    } else if(G->color[u] == GRAY || G->color[u] == WHITE){
        append(L, NIL);
    } else {
        getPath(L, G, G->parent[u]);
        append(L, u);
    }
}



/*** Manipulation procedures ***/
// makeNull() - deletes all edges of G, restoring it to its original (no edge) state.
void makeNull(Graph G){
    for(int i = 1; i < getOrder(G); i++){
        clear(G->adj[i]);
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->dist[i] = INF;
    }
    G->size = 0;
    G->order = 0;
    G->source = NIL;
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

// BFS() - runs the BFS algorithm on the Graph G with source s, setting the color, distance, parent, and source fields of G accordingly.

void BFS(Graph G, int s){
    int u, v = 0;
    G->source = s;
    for(int i = 1; i < getOrder(G)+1; i++){
        G->color[i] = WHITE;
        G->dist[i] = INF;
        G->parent[i] = NIL;
    }
    G->color[s] = GRAY;
    G->dist[s] = 0;
    G->parent[s] = NIL;
    
    List Q = newList();
    append(Q, s);
    
    while(length(Q) != 0){
        moveFront(Q);
        u = get(Q);
        deleteFront(Q);
        
        moveFront(G->adj[u]);
        for(int j = 0; j < length(G->adj[u]); j++){
            v = get(G->adj[u]);
            if(G->color[v] == WHITE){
                G->color[v] = GRAY;
                G->dist[v] = G->dist[u] + 1;
                G->parent[v] = u;
                append(Q, v);
            }
            moveNext(G->adj[u]);
        }
        G->color[u] = BLACK;
    }
    freeList(&Q);
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


/*** Other operations ***/
// printGraph() - prints the adjacency list representation of G to the file pointed to by out
void printGraph(FILE* out, Graph G){
    for(int i = 1; i < getOrder(G)+1; i++){
        fprintf(out, "%d: ", i);
        printList(out, G->adj[i]);
        fprintf(out, "\n");
    }
}


