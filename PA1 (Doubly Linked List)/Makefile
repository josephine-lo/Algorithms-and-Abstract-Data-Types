#------------------------------------------------------------------------------
# Josephine Lo, 1689289
# CSE101 - PA1
# 10-12-19
#-----------------------------------------------------------------------------
# Makefile (for CSE 101 Programming Assignment 1) - compiles source code
#       make                   makes Lex
#       make ListClient        makes ListClient
#------------------------------------------------------------------------------

Lex : Lex.o List.o
	gcc -o Lex Lex.o List.o

Lex.o : Lex.c List.h
	gcc -c -std=c99  -g -Wall Lex.c

ListClient: ListClient.o List.o
	gcc -o ListClient ListClient.o List.o

ListClient.o : ListClient.c List.h
	gcc -c -std=c99 -Wall -g  ListClient.c

List.o : List.c List.h
	gcc -c -std=c99 -Wall -g List.c

clean :
	rm -f Lex ListClient Lex.o ListClient.o List.o

