/*----------------------------------------------------------------------------------
 * Josephine Lo, 1689289, jowlo
 * CSE101 - PA4
 * November 29th, 2019
 *----------------------------------------------------------------------------------
 * FindPath.c - A client program for the Graph ADT to find the shortest paths
 *      between pairs of vectors.
 *----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(int argc, char * argv[]){
    FILE *in, *out;
    int num = 0;
    int source = 0, dest = 0, dist = 0;
    
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
            addEdge(G, source, dest);
        } else {
            break;
        }
    }

    printGraph(out, G);
    fprintf(out, "\n");

    List L = newList();
    while (!feof(in) ) {
        fscanf(in, "%d %d", &source, &dest);
        if(source != 0 && dest != 0){
            BFS(G, source);
            getPath(L, G, dest);
            dist = getDist(G, dest);
            
            fprintf(out, "The distance from %d to %d is ", source, dest);
            if (dist == INF) {
                fprintf(out, "infinity\n");
                fprintf(out, "No %d-%d path exists\n\n", source, dest);
                clear(L);
                continue;
            } else {
                fprintf(out, "%d\n", dist);
            }

            fprintf(out, "A shortest %d-%d path is: ", source, dest);
            printList(out, L);
            fprintf(out, "\n\n");

            clear(L);

        } else {
            break;
        }

    }
    freeList(&L);
    freeGraph(&G);

    // close files
    fclose(in);
    fclose(out);

    return 0;

}



