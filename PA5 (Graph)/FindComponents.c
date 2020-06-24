/*----------------------------------------------------------------------------
* Josephine Lo, jowlo, 1689289
* CSE101 - PA5
* December 6, 2019
* --------------------------------------------------------------------------
* FindComponents.c - client module of the Graph ADT that takes two command
*       line arguments to determine the SCC(s) of a diagraph
* --------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(int argc, char* argv[]){
    FILE *in, *out;
    int num = 0;
    int source = 0, dest = 0;
    
    if(argc != 3){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    
    if(in == NULL){
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    if(out == NULL){
        printf("Unable to open file %s for wriitng\n", argv[2]);
        exit(EXIT_FAILURE);
    }
    
    fscanf(in, "%d", &num);
    Graph G = newGraph(num);
    
    while (!feof(in)){
       fscanf(in, "%d %d", &source, &dest);
       if (source != 0 && dest != 0) {
           addArc(G, source, dest);
       } else {
           break;
       }
   }
    
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);
    fprintf(out, "\n");
    
    List L = newList();
    for(int i = 1; i < getOrder(G)+1; i++){
        append(L, i);
    }
    
    int SCC = 0;
    DFS(G, L);
    Graph H = NULL;
    H = transpose(G);
    DFS(H, L);
    
    for(int i = 1; i < getOrder(H)+1; i++){
        if(getParent(H, i) == NIL){
            SCC++;
        }
    }
    
    fprintf(out, "G contains %d strongly connected component", SCC);
    if(SCC > 1){
        fprintf(out, "s:\n");
    } else {
        fprintf(out, ":\n");
    }
    
    List M[SCC];
    int num1 = SCC;
    
    for(int i = 0; i < SCC; i++){
       M[i] = newList();
    }
    
    moveFront(L);
    while(index(L) != -1){
        if(getParent(H, get(L)) == NIL){
            num1--;
        }
        if(num1 == SCC){
            break;
        }
        append(M[num1], get(L));
        moveNext(L);
    }
    
    for(int i = 0; i < SCC; i++){
        fprintf(out, "Component %d: ", i+1);
        printList(out, M[i]);
        fprintf(out, "\n");
        clear(M[i]);
    }
 
    return 0;
}
