AS	=as
LD	=ld
CC	=gcc
MAKE	=make
CPP	=$(CC) -E
AR	=ar
STRIP	=strip
PKGCONF =pkg-config

CFLAGS = -g -DDEBUG -I../src
LDFLAGS = -L../lib -lcb -lm
ifdef WINDIR
    CFLAGS += -DWINDIR
    LDFLAGS += `$(PKGCONF) --libs iconv`
else
    CFLAGS += -m32
endif

FROMDOS=dos2unix
TODOS=dos2unix

LIBS	=
SUBDIRS	=

SRCS = test.c d4simple.c bank.c

all: $(SRCS)
	$(CC) $(CFLAGS) -o test.bin test.c conv.c $(LDFLAGS)
	$(CC) $(CFLAGS) -o d4simple.bin d4simple.c $(LDFLAGS)
	$(CC) $(CFLAGS) -o bank.bin bank.c $(LDFLAGS)

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

clean:
	rm -f core *.[oas] *~ *.bin *.log *.cgp *.ntx *.cdx *test.dbf
