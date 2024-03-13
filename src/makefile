CFLAGS = -g -DDEBUG -trigraphs
ifdef WINDIR
    CFLAGS += -DWINDIR
else
    CFLAGS += -m32
endif

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

LIB_CB = libcb
VER_CB = 6.4

LIBS	=
SUBDIRS	=

OBJS = b4block.o c4bcd.o c4blast.o c4buffer.o c4.o c4code.o c4com2.o c4com.o c4conect.o c4conlow.o c4const.o c4hook.o c4thread.o c4trans.o c4util.o \
    d4append.o d4bottom.o d4close.o d4create.o d4data.o d4date.o d4extra.o d4field.o d4file.o d4flush.o d4fresh.o d4go.o d4index.o d4info.o d4inline.o \
    d4lock.o d4modify.o d4open.o d4opt.o d4pack.o d4positi.o d4remove.o d4seek.o d4skip.o d4tag.o d4top.o d4unlock.o d4write.o d4zap.o df4lock.o df4unlok.o \
    e4calc_2.o e4calc.o e4error.o e4event.o e4expr.o e4functi.o e4not_s.o e4parse.o  e4string.o \
    f4ass_f.o f4char.o f4close.o f4create.o f4cur.o f4double.o f4dttime.o f4field.o f4file.o f4filese.o f4flag.o \
    f4flush.o f4info.o f4int.o f4lock.o f4long.o f4memo.o f4null.o f4open.o f4opt.o f4ptr.o f4str.o f4temp.o f4true.o f4write.o \
    i4add.o i4addtag.o i4check.o i4create.o i4dump.o i4index.o i4info.o i4init.o i4key.o i4lock.o i4ntag.o i4positi.o i4remove.o i4tag.o i4thread.o \
    l4link.o l4lock_c.o l4mutex.o m4check.o m4create.o m4file.o m4map.o m4memo.o m4memory.o o4opt.o \
    r4area.o r4bit.o r4drive2.o r4driver.o r4group.o r4log.o r4obj.o r4regs.o r4reinde.o r4reindx.o r4relate.o r4report.o r4save_2.o r4save.o r4style.o r4total.o \
    s4init.o s4initfr.o s4next.o s4quick.o s4signal.o s4sort.o sema4.o u4name.o u4util.o
#   e4str2.o p4pascal.o v4basic.o

OBJS_PORT = char.o str.o

all: $(OBJS_PORT) $(OBJS)
	$(AR) rc ../lib/$(LIB_CB)-$(VER_CB).a $(OBJS_PORT) $(OBJS)

install: all
	ln -s ../lib/$(LIB_CB)-$(VER_CB).a  ../lib/$(LIB_CB).a

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


char.o: port/char.c
	$(CC) $(CFLAGS) -c port/char.c
str.o: port/str.c
	$(CC) $(CFLAGS) -c port/str.c

b4block.o: b4block.c
	$(CC) $(CFLAGS) -c b4block.c
c4bcd.o: c4bcd.c
	$(CC) $(CFLAGS) -c c4bcd.c
c4blast.o: c4blast.c
	$(CC) $(CFLAGS) -c c4blast.c
c4buffer.o: c4buffer.c
	$(CC) $(CFLAGS) -c c4buffer.c
c4.o: c4.c
	$(CC) $(CFLAGS) -c c4.c
c4code.o: c4code.c
	$(CC) $(CFLAGS) -c c4code.c
c4com2.o: c4com2.c
	$(CC) $(CFLAGS) -c c4com2.c
c4com.o: c4com.c
	$(CC) $(CFLAGS) -c c4com.c
c4conect.o: c4conect.c
	$(CC) $(CFLAGS) -c c4conect.c
c4conlow.o: c4conlow.c
	$(CC) $(CFLAGS) -c c4conlow.c
c4const.o: c4const.c
	$(CC) $(CFLAGS) -c c4const.c
c4hook.o: c4hook.c
	$(CC) $(CFLAGS) -c c4hook.c
c4thread.o: c4thread.c
	$(CC) $(CFLAGS) -c c4thread.c
c4trans.o: c4trans.c
	$(CC) $(CFLAGS) -c c4trans.c
c4util.o: c4util.c
	$(CC) $(CFLAGS) -c c4util.c

d4append.o: d4append.c
	$(CC) $(CFLAGS) -c d4append.c
d4bottom.o: d4bottom.c
	$(CC) $(CFLAGS) -c d4bottom.c
d4close.o: d4close.c
	$(CC) $(CFLAGS) -c d4close.c
d4create.o: d4create.c
	$(CC) $(CFLAGS) -c d4create.c
d4data.o: d4data.c
	$(CC) $(CFLAGS) -c d4data.c
d4date.o: d4date.c
	$(CC) $(CFLAGS) -c d4date.c
d4extra.o: d4extra.c
	$(CC) $(CFLAGS) -c d4extra.c
d4field.o: d4field.c
	$(CC) $(CFLAGS) -c d4field.c
d4file.o: d4file.c
	$(CC) $(CFLAGS) -c d4file.c
d4flush.o: d4flush.c
	$(CC) $(CFLAGS) -c d4flush.c
d4fresh.o: d4fresh.c
	$(CC) $(CFLAGS) -c d4fresh.c
d4go.o: d4go.c
	$(CC) $(CFLAGS) -c d4go.c
d4index.o: d4index.c
	$(CC) $(CFLAGS) -c d4index.c
d4info.o: d4info.c
	$(CC) $(CFLAGS) -c d4info.c
d4inline.o: d4inline.c
	$(CC) $(CFLAGS) -c d4inline.c
d4lock.o: d4lock.c
	$(CC) $(CFLAGS) -c d4lock.c
d4modify.o: d4modify.c
	$(CC) $(CFLAGS) -c d4modify.c
d4open.o: d4open.c
	$(CC) $(CFLAGS) -c d4open.c
d4opt.o: d4opt.c
	$(CC) $(CFLAGS) -c d4opt.c
d4pack.o: d4pack.c
	$(CC) $(CFLAGS) -c d4pack.c
d4positi.o: d4positi.c
	$(CC) $(CFLAGS) -c d4positi.c
d4remove.o: d4remove.c
	$(CC) $(CFLAGS) -c d4remove.c
d4seek.o: d4seek.c
	$(CC) $(CFLAGS) -c d4seek.c
d4skip.o: d4skip.c
	$(CC) $(CFLAGS) -c d4skip.c
d4tag.o: d4tag.c
	$(CC) $(CFLAGS) -c d4tag.c
d4top.o: d4top.c
	$(CC) $(CFLAGS) -c d4top.c
d4unlock.o: d4unlock.c
	$(CC) $(CFLAGS) -c d4unlock.c
d4write.o: d4write.c
	$(CC) $(CFLAGS) -c d4write.c
d4zap.o: d4zap.c
	$(CC) $(CFLAGS) -c d4zap.c
df4lock.o: df4lock.c
	$(CC) $(CFLAGS) -c df4lock.c
df4unlok.o: df4unlok.c
	$(CC) $(CFLAGS) -c df4unlok.c

e4calc_2.o: e4calc_2.c
	$(CC) $(CFLAGS) -c e4calc_2.c
e4calc.o: e4calc.c
	$(CC) $(CFLAGS) -c e4calc.c
e4error.o: e4error.c
	$(CC) $(CFLAGS) -c e4error.c
e4event.o: e4event.c
	$(CC) $(CFLAGS) -c e4event.c
e4expr.o: e4expr.c
	$(CC) $(CFLAGS) -c e4expr.c
e4functi.o: e4functi.c
	$(CC) $(CFLAGS) -c e4functi.c
e4not_s.o: e4not_s.c
	$(CC) $(CFLAGS) -c e4not_s.c
e4parse.o: e4parse.c
	$(CC) $(CFLAGS) -c e4parse.c
e4str2.o: e4str2.c
	$(CC) $(CFLAGS) -c e4str2.c
e4string.o: e4string.c
	$(CC) $(CFLAGS) -c e4string.c

f4ass_f.o: f4ass_f.c
	$(CC) $(CFLAGS) -c f4ass_f.c
f4char.o: f4char.c
	$(CC) $(CFLAGS) -c f4char.c
f4close.o: f4close.c
	$(CC) $(CFLAGS) -c f4close.c
f4create.o: f4create.c
	$(CC) $(CFLAGS) -c f4create.c
f4cur.o: f4cur.c
	$(CC) $(CFLAGS) -c f4cur.c
f4double.o: f4double.c
	$(CC) $(CFLAGS) -c f4double.c
f4dttime.o: f4dttime.c
	$(CC) $(CFLAGS) -c f4dttime.c
f4field.o: f4field.c
	$(CC) $(CFLAGS) -c f4field.c
f4file.o: f4file.c
	$(CC) $(CFLAGS) -c f4file.c
f4filese.o: f4filese.c
	$(CC) $(CFLAGS) -c f4filese.c
f4flag.o: f4flag.c
	$(CC) $(CFLAGS) -c f4flag.c
f4flush.o: f4flush.c
	$(CC) $(CFLAGS) -c f4flush.c
f4info.o: f4info.c
	$(CC) $(CFLAGS) -c f4info.c
f4int.o: f4int.c
	$(CC) $(CFLAGS) -c f4int.c
f4lock.o: f4lock.c
	$(CC) $(CFLAGS) -c f4lock.c
f4long.o: f4long.c
	$(CC) $(CFLAGS) -c f4long.c
f4memo.o: f4memo.c
	$(CC) $(CFLAGS) -c f4memo.c
f4null.o: f4null.c
	$(CC) $(CFLAGS) -c f4null.c
f4open.o: f4open.c
	$(CC) $(CFLAGS) -c f4open.c
f4opt.o: f4opt.c
	$(CC) $(CFLAGS) -c f4opt.c
f4ptr.o: f4ptr.c
	$(CC) $(CFLAGS) -c f4ptr.c
f4str.o: f4str.c
	$(CC) $(CFLAGS) -c f4str.c
f4temp.o: f4temp.c
	$(CC) $(CFLAGS) -c f4temp.c
f4true.o: f4true.c
	$(CC) $(CFLAGS) -c f4true.c
f4write.o: f4write.c
	$(CC) $(CFLAGS) -c f4write.c

i4add.o: i4add.c
	$(CC) $(CFLAGS) -c i4add.c
i4addtag.o: i4addtag.c
	$(CC) $(CFLAGS) -c i4addtag.c
i4check.o: i4check.c
	$(CC) $(CFLAGS) -c i4check.c
i4create.o: i4create.c
	$(CC) $(CFLAGS) -c i4create.c
i4dump.o: i4dump.c
	$(CC) $(CFLAGS) -c i4dump.c
i4index.o: i4index.c
	$(CC) $(CFLAGS) -c i4index.c
i4info.o: i4info.c
	$(CC) $(CFLAGS) -c i4info.c
i4init.o: i4init.c
	$(CC) $(CFLAGS) -c i4init.c
i4key.o: i4key.c
	$(CC) $(CFLAGS) -c i4key.c
i4lock.o: i4lock.c
	$(CC) $(CFLAGS) -c i4lock.c
i4ntag.o: i4ntag.c
	$(CC) $(CFLAGS) -c i4ntag.c
i4positi.o: i4positi.c
	$(CC) $(CFLAGS) -c i4positi.c
i4remove.o: i4remove.c
	$(CC) $(CFLAGS) -c i4remove.c
i4tag.o: i4tag.c
	$(CC) $(CFLAGS) -c i4tag.c
i4thread.o: i4thread.c
	$(CC) $(CFLAGS) -c i4thread.c

l4link.o: l4link.c
	$(CC) $(CFLAGS) -c l4link.c
l4lock_c.o: l4lock_c.c
	$(CC) $(CFLAGS) -c l4lock_c.c
l4mutex.o: l4mutex.c
	$(CC) $(CFLAGS) -c l4mutex.c
m4check.o: m4check.c
	$(CC) $(CFLAGS) -c m4check.c
m4create.o: m4create.c
	$(CC) $(CFLAGS) -c m4create.c
m4file.o: m4file.c
	$(CC) $(CFLAGS) -c m4file.c
m4map.o: m4map.c
	$(CC) $(CFLAGS) -c m4map.c
m4memo.o: m4memo.c
	$(CC) $(CFLAGS) -c m4memo.c
m4memory.o: m4memory.c
	$(CC) $(CFLAGS) -c m4memory.c
o4opt.o: o4opt.c
	$(CC) $(CFLAGS) -c o4opt.c
p4pascal.o: p4pascal.c
	$(CC) $(CFLAGS) -c p4pascal.c

r4area.o: r4area.c
	$(CC) $(CFLAGS) -c r4area.c
r4bit.o: r4bit.c
	$(CC) $(CFLAGS) -c r4bit.c
r4drive2.o: r4drive2.c
	$(CC) $(CFLAGS) -c r4drive2.c
r4driver.o: r4driver.c
	$(CC) $(CFLAGS) -c r4driver.c
r4group.o: r4group.c
	$(CC) $(CFLAGS) -c r4group.c
r4log.o: r4log.c
	$(CC) $(CFLAGS) -c r4log.c
r4obj.o: r4obj.c
	$(CC) $(CFLAGS) -c r4obj.c
r4regs.o: r4regs.c
	$(CC) $(CFLAGS) -c r4regs.c
r4reinde.o: r4reinde.c
	$(CC) $(CFLAGS) -c r4reinde.c
r4reindx.o: r4reindx.c
	$(CC) $(CFLAGS) -c r4reindx.c
r4relate.o: r4relate.c
	$(CC) $(CFLAGS) -c r4relate.c
r4report.o: r4report.c
	$(CC) $(CFLAGS) -c r4report.c
r4save_2.o: r4save_2.c
	$(CC) $(CFLAGS) -c r4save_2.c
r4save.o: r4save.c
	$(CC) $(CFLAGS) -c r4save.c
r4style.o: r4style.c
	$(CC) $(CFLAGS) -c r4style.c
r4total.o: r4total.c
	$(CC) $(CFLAGS) -c r4total.c

s4init.o: s4init.c
	$(CC) $(CFLAGS) -c s4init.c
s4initfr.o: s4initfr.c
	$(CC) $(CFLAGS) -c s4initfr.c
s4next.o: s4next.c
	$(CC) $(CFLAGS) -c s4next.c
s4quick.o: s4quick.c
	$(CC) $(CFLAGS) -c s4quick.c
s4signal.o: s4signal.c
	$(CC) $(CFLAGS) -c s4signal.c
s4sort.o: s4sort.c
	$(CC) $(CFLAGS) -c s4sort.c
sema4.o: sema4.c
	$(CC) $(CFLAGS) -c sema4.c
u4name.o: u4name.c
	$(CC) $(CFLAGS) -c u4name.c
u4util.o: u4util.c
	$(CC) $(CFLAGS) -c u4util.c
v4basic.o: v4basic.c
	$(CC) $(CFLAGS) -c v4basic.c

clean:
	rm -f core *.[oas] *~ *.bin *.log
	rm -f ../lib/*.a ../lib/*.so
