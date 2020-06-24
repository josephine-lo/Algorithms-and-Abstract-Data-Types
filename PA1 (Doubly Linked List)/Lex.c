/*----------------------------------------------------------------------------
 * Josephine Lo, 1689289
 * CSE101 - PA1
 * 10-12-19
 * --------------------------------------------------------------------------
 *  Lex.c - indirectly sorts the input file by creating a List and sorting
 *  	the indicies of the list in lexicographic ordering.
 * --------------------------------------------------------------------------*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"

#define MAX_LEN 160


int main(int argc, char* argv[]){
    FILE *in, *out;
    int count = 0;
    char line[MAX_LEN];

    
    if(argc != 3){
        fprintf(stderr, "Usage: %s <input file><output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    
    if(in == NULL){
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    if(out == NULL){
        printf("Unable to open file %s for reading\n", argv[2]);
        exit(EXIT_FAILURE);
    }
    
    char c;
    for(c = getc(in); c != EOF; c = getc(in)){
        if (c == '\n'){
            count++;
        }
    }
    count++;
    //fprintf(out, "file has %d lines\n", count);
    
    char arr[count][MAX_LEN];
    fclose(in);
    List L = newList();
    
    in = fopen(argv[1], "r");
    int ind = 0;        //index of arr

    
    //place file contents into array        arr[] contains elements
    while(fgets(line, MAX_LEN, in) != NULL)  {
        strcpy(arr[ind], line);
        ind++;
    }
    

    //use insertion sort to append elements into list
    append(L, 0);
    int flag = 0;
    int p = 0;
    for(int i = 1; i < count; i++){
        moveFront(L);
        flag = 0;
        while(index(L) >= 0){
	    p = get(L);
	    if(strcmp(arr[i], arr[p]) < 0){
               insertBefore(L, i);
               flag = 1;
               break;
	    }
            moveNext(L);
        }
        if(flag != 1){
            append(L, i);
        }
    }
    if(length(L) > 1){
 	   for(moveFront(L); index(L) >= 0; moveNext(L)){
       		 fprintf(out, "%s", arr[get(L)]);
   	   }
    }else if(length(L) == 1){
	fprintf(out, "%s", arr[0]);
    }
    
    fclose(in);
    fclose(out);
    freeList(&L);
    
}


