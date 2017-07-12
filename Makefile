CC=gcc
CFLAGS=-I.

compilador: lex.yy.c
	gcc lex.yy.c -o compilador

lex.yy.c: lexico.l
	lex lexico.l

clean:
	-rm -f compilador.o
	-rm -f compilador
	-rm -f lex.yy.c
