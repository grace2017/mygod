CC:=gcc
TARGET:=mygod
CFLAGS:=-g
CFLAGS+=-o

$(TARGET) : y.tab.c lex.yy.c mygod.c main.c
	gcc $^ $(CFLAGS) $@
y.tab.h : god.y
	bison --yacc -dv $<
y.tab.c : god.y
	bison --yacc -dv $<
lex.yy.c : god.l
	flex $<

clean:
	rm -rf lex.yy.c
	rm -rf y.tab.h
	rm -rf y.tab.c
	rm -rf y.output
	rm -rf mygod 
