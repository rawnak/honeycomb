SHELL := /bin/bash

all: libs

zco: lex yacc
	gcc lex.yy.c zco.tab.c -o zco

lex: zco.l
	flex zco.l

yacc: zco.y
	bison --debug -v --verbose -d zco.y

clean:
	rm -f lex.yy.c y.output zco.tab.c zco.tab.h zco

z-object.o: zco z-object.zco
	./zco z-object.zco
	gcc -I. -c z-object.c -o z-object.o

z-vector.o: zco z-vector.zco
	./zco z-vector.zco
	gcc -I. -c z-vector.c -o z-vector.o

z-vector-iter.o: zco z-vector-iter.zco
	./zco z-vector-iter.zco
	gcc -I. -c z-vector-iter.c -o z-vector-iter.o

libs: z-object.o z-vector-iter.o z-vector.o


