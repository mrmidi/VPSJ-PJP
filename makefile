CC=gcc
LEX=flex
YACC=bison
CFLAGS=-Wall

all: turbopjp

turbopjp: turbopjp.tab.c lex.yy.c
	$(CC) $(CFLAGS) turbopjp.tab.c lex.yy.c -o $@ -lfl -lm

lex.yy.c: turbopjp.l
	$(LEX) $<

turbopjp.tab.c: turbopjp.y
	$(YACC) -d -v $<

debug: CFLAGS += -g
# debug: VERBOSE=-V
debug: turbopjp

.PHONY: clean

clean:
	rm -f lex.yy.c turbopjp.tab.c turbopjp.tab.h turbopjp *.output
