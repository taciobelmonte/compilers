CC=gcc
CFLAGS=-I.

all:
	mv sintatico.c sintatico.y
	bison -d sintatico.y  -v
	mv sintatico.tab.h sintatico.h
	mv sintatico.tab.c sintatico.y.c
	flex lexico.l
	mv lex.yy.c sintatico.lex.c
	gcc -g -c sintatico.lex.c -o sintatico.lex.o
	gcc -g -c sintatico.y.c -o sintatico.y.o
	gcc -g -o compilador sintatico.lex.o sintatico.y.o
	mv sintatico.y sintatico.c

compilador: lex.yy.c
	gcc lex.yy.c -o compilador

lex.yy.c: lexico.l
	lex lexico.l

clean:
	rm -f compilador
	rm -f sandbox/out*

runtests: all
	./run-sandbox
