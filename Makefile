SHELL := /bin/bash
CC := gcc
CFLAGS := -pipe -g -fstack-protector-all
ENV := DISTCC_LOG=distcc.log
ZCO := ./zco

all: zco-test

zco: zco.l zco.y
	flex zco.l
	bison --debug -v --verbose -d zco.y
	${ENV} ${CC} ${CFLAGS} -I. -lm lex.yy.c zco.tab.c z-string.c z-string-iter.c z-vector.c z-vector-iter.c z-object.c zco-type.c -o zco

clean:
	rm -f lex.yy.c zco.output zco.tab.c zco.tab.h
	rm -f *.so *.o
	rm -f zco zco-test

# type objects
z-object.o: zco z-object.zco
	${ZCO} z-object.zco
	${ENV} ${CC} ${CFLAGS} -fPIC -I. -c z-object.c -o z-object.o

z-vector.o: zco z-vector.zco
	${ZCO} z-vector.zco
	${ENV} ${CC} ${CFLAGS} -fPIC -I. -c z-vector.c -o z-vector.o

z-vector-iter.o: zco z-vector-iter.zco
	${ZCO} z-vector-iter.zco
	${ENV} ${CC} ${CFLAGS} -fPIC -I. -c z-vector-iter.c -o z-vector-iter.o

z-string.o: zco z-string.zco
	${ZCO} z-string.zco
	${ENV} ${CC} ${CFLAGS} -fPIC -I. -c z-string.c -o z-string.o

z-string-iter.o: zco z-string-iter.zco
	${ZCO} z-string-iter.zco
	${ENV} ${CC} ${CFLAGS} -fPIC -I. -c z-string-iter.c -o z-string-iter.o

z-map.o: zco z-map.zco
	${ZCO} z-map.zco
	${ENV} ${CC} ${CFLAGS} -fPIC -I. -c z-map.c -o z-map.o

z-map-iter.o: zco z-map-iter.zco
	${ZCO} z-map-iter.zco
	${ENV} ${CC} ${CFLAGS} -fPIC -I. -c z-map-iter.c -o z-map-iter.o

# TARGET: libzclib.so
zco-type.o: zco-type.h zco-type.c
	${ENV} ${CC} ${CFLAGS} -fPIC -I. -c zco-type.c -o zco-type.o

libzclib.so: zco-type.o z-object.o z-vector-iter.o z-vector.o z-string-iter.o z-string.o z-map-iter.o z-map.o
	${ENV} ${CC} -shared zco-type.o z-object.o z-vector-iter.o z-vector.o z-string-iter.o z-string.o z-map-iter.o z-map.o -o libzclib.so

# test driver objects
z-vector-test.o: z-vector-test.c zco-test.h
	${ENV} ${CC} ${CFLAGS} -I. -c z-vector-test.c -o z-vector-test.o

z-string-test.o: z-string-test.c zco-test.h
	${ENV} ${CC} ${CFLAGS} -I. -c z-string-test.c -o z-string-test.o

z-map-test.o: z-map-test.c zco-test.h
	${ENV} ${CC} ${CFLAGS} -I. -c z-map-test.c -o z-map-test.o

# TARGET: zco-test
zco-test.o: zco-test.c zco-test.h
	${ENV} ${CC} -I. -c zco-test.c -o zco-test.o

zco-test: libzclib.so zco-test.o z-vector-test.o z-string-test.o z-map-test.o 
	${ENV} ${CC} -L. -lzclib -lm zco-test.o z-vector-test.o z-string-test.o z-map-test.o -o zco-test


