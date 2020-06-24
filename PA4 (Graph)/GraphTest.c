/*-----------------------------------------------------------------------------
 * Josephine Lo, 1689289, jowlo
 * CSE101 - PA4
 * November 29th, 2019
 *-----------------------------------------------------------------------------
 * GraphTest.c - A test file for the Graph ADT
 *----------------------------------------------------------------------------*/

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
    int i, s, max, d, n = 35;
    List  A = newList();
    List  E = newList();
    Graph G = NULL;

    // Build graph G
    G = newGraph(n);
    for(i = 1; i < n; i++){
        if(i % 7 != 0){
           addEdge(G, i, i+1);
        }
        if(i <= 32){
           addEdge(G, i, i+3);
        }
    }
    addEdge(G, 9, 33);
    addEdge(G, 17, 33);
    addEdge(G, 14, 33);

    printGraph(stdout, G);
    printf("\norder: %d\n", getOrder(G));
    printf("size: %d\n", getSize(G));
    printf("source: %d\n", getSource(G));

    getPath(A, G, 9);
    addArc(G, 9, 33);

    for(s = 1; s <= n; s++){
        BFS(G, s);
        max = getDist(G, 1);
        for(i = 2; i <= n; i++){
             d = getDist(G, i);
             max = (max<d ? d : max);
        }
        append(E, max);
    }


    makeNull(G);
    printGraph(stdout, G);

    freeList(&A);
    freeList(&E);
    freeGraph(&G);

    return(0);
}

