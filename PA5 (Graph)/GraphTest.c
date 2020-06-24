/*----------------------------------------------------------------------------
* Josephine Lo, jowlo, 1689289
* CSE101 - PA5
* December 6, 2019
* --------------------------------------------------------------------------
*  GraphTest.c - test file to test the operations of the Graph ADT
* --------------------------------------------------------------------------*/

#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"


int main(int argc, char* argv[]){
   int i, n=9;
   List L = newList();
   Graph G = newGraph(n);
   Graph H = NULL, J = NULL;

   for(i=1; i<=n; i++) append(L, i);

   addArc(G, 1,2);
   addArc(G, 1,6);
   addArc(G, 2,3);
   addArc(G, 2,4);
   addArc(G, 3,2);
   addArc(G, 3,3);
   addArc(G, 3,6);
   addArc(G, 3,7);
   addArc(G, 3,9);
   addArc(G, 4,5);
   addArc(G, 4,8);
   addArc(G, 5,9);
   addArc(G, 6,7);
   addArc(G, 8,4);
   addArc(G, 8,7);
   printGraph(stdout, G);

   DFS(G, L);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, L);
   fprintf(stdout, "\n");

   fprintf(stdout, "order: %d", getOrder(G));
   fprintf(stdout, "\n");
   fprintf(stdout, "size: %d", getSize(G));
   fprintf(stdout, "\n");
    
   H = transpose(G);
   J = copyGraph(G);
   fprintf(stdout, "\n");
   printGraph(stdout, H);
   fprintf(stdout, "\n");
   printGraph(stdout, J);
   fprintf(stdout, "\n");

   DFS(H, L);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(H, i), getFinish(H, i), getParent(J, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, L);
   fprintf(stdout, "\n");

   freeList(&L);
   freeGraph(&G);
   freeGraph(&H);
   freeGraph(&J);
   return(0);
}
