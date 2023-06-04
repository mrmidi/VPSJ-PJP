CC=gcc
LEX=flex
YACC=bison
CFLAGS=-Wall

all: pjp

pjp: pjp++.tab.c lex.yy.c
	$(CC) $(CFLAGS) pjp++.tab.c lex.yy.c -o $@ -lfl -lm

lex.yy.c: pjp++.l
	$(LEX) $<

pjp++.tab.c: pjp++.y
	$(YACC) -d -v $<

debug: CFLAGS += -g
# debug: VERBOSE=-V
debug: pjp

.PHONY: clean

clean:
	rm -f lex.yy.c pjp++.tab.c pjp++.tab.h pjp *.output
