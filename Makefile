SHELL := /bin/bash
CC := /usr/bin/gcc
CFLAGS := -g

all: zco-test

zco: zco.l zco.y
	flex zco.l
	bison --debug -v --verbose -d zco.y
	${CC} ${CFLAGS} lex.yy.c zco.tab.c -o zco

clean:
	rm -f lex.yy.c y.output zco.tab.c zco.tab.h zco *.so *.o

# type objects
z-object.o: zco z-object.zco
	./zco z-object.zco
	${CC} ${CFLAGS} -fPIC -I. -c z-object.c -o z-object.o

z-vector.o: zco z-vector.zco
	./zco z-vector.zco
	${CC} ${CFLAGS} -fPIC -I. -c z-vector.c -o z-vector.o

z-vector-iter.o: zco z-vector-iter.zco
	./zco z-vector-iter.zco
	${CC} ${CFLAGS} -fPIC -I. -c z-vector-iter.c -o z-vector-iter.o

# TARGET: libzclib.so
zco-type.o: zco-type.h zco-type.c
	${CC} ${CFLAGS} -fPIC -I. -c zco-type.c -o zco-type.o

libzclib.so: zco-type.o z-object.o z-vector-iter.o z-vector.o
	${CC} -shared zco-type.o z-object.o z-vector-iter.o z-vector.o -o libzclib.so

# test driver objects
z-vector-test.o: z-vector-test.c zco-test.h
	${CC} ${CFLAGS} -I. -c z-vector-test.c -o z-vector-test.o


# TARGET: zco-test
zco-test.o: zco-test.c zco-test.h
	${CC} -I. -c zco-test.c -o zco-test.o

zco-test: libzclib.so zco-test.o z-vector-test.o
	${CC} -L. -lzclib zco-test.o z-vector-test.o -o zco-test



