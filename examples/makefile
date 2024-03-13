CFLAGS = -g -DDEBUG

FROMDOS=dos2unix
TODOS=dos2unix

AS	=as
LD	=ld
CC	=gcc
MAKE	=make
CPP	=$(CC) -E
AR	=ar
STRIP	=strip
PKGCONF =pkg-config

LIBS	=
SUBDIRS	=

OBJS = capieg.o

all: $(OBJS)
	$(CC) -o capieg.bin $(OBJS) -L../lib -lcb -lm
#	$(CC) -o capieg.bin $(OBJS) ../lib/libcb.a -lm

fromdos:
	$(FROMDOS) makefile
	$(FROMDOS) *.c
	$(FROMDOS) *.h
todos:
	$(TODOS) makefile
	$(TODOS) *.c
	$(TODOS) *.h

touch:
	touch makefile
	touch *.c
	touch *.h

capieg.o: capieg.c
	$(CC) $(CFLAGS) -I../src -c capieg.c
ex0.o: ex0.c
	$(CC) $(CFLAGS) -I../src -c ex0.c
ex1.o: ex1.c
	$(CC) $(CFLAGS) -I../src -c ex1.c

clean:
	rm -f core *.[oas] *~ *.bin *.log
