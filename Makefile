CC=gcc
CFLAGS=-I.

compilador: lex.yy.c
	gcc lex.yy.c -o compilador

clean:
	-rm -f compilador.o
	-rm -f compilador