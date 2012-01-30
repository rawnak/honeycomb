all: lex yacc
	gcc lex.yy.c zco.tab.c -o zco

lex: zco.l
	flex zco.l

yacc: zco.y
	bison --debug -v --verbose -d zco.y

clean:
	rm -f lex.yy.c y.output zco.tab.c zco.tab.h zco

test: all
	./zco test.zco && echo " ----- input -----" && cat test.zco && echo " ----- header -----" && cat test.h && echo " ----- source -----" && cat test.c

