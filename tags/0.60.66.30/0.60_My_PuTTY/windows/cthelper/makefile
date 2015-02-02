#-- putty-0.59/windows/cthelper/Makefile	1969-12-31 17:00:00.000000000 -0700
#++ putty-0.59-cygterm/windows/cthelper/Makefile	2007-02-02 15:08:58.000000000 -0700
#@ -0,0 +1,46 @@
TARGET_ARCH = -mcygwin
LINK = $(CC)
CFLAGS = $(DBUG_CFLAGS) $(DEFINES) $(INCLUDE) $(PLATFORM) -DCYGTERMPORT
DEFINES = $(DBUG_DEFINES)
INCLUDE = $(DBUG_INCLUDE)
LDFLAGS = -s $(DBUG_LDFLAGS)
q = @echo $@;

ifdef DEBUG
DBUG = /usr/local
#DBUG = /home/dbug
#DBUG = .
DBUG_CFLAGS = -g
DBUG_DEFINES = -DDEBUG -DDEBUG_CHILD
DBUG_INCLUDE = -I$(DBUG)/include
DBUG_LDFLAGS = -L$(DBUG)/lib
DBUG_OBJ = dump.o
LDLIBS = -ldbug
else
DBUG_DEFINES = -DDBUG_OFF
endif

## SFU (INTERIX) needs these also
APUE_OBJ = ptyfork.o ptyopen.o error.o

#SRC = buffer.c buffer.h dump.c debug.h
SRC = cthelper.c buffer.c buffer.h dump.c debug.h
#OBJ = cthelper.o buffer.o message.o $(APUE_OBJ) $(DBUG_OBJ)
OBJ = buffer.o message.o $(APUE_OBJ) $(DBUG_OBJ)

default: all
all: cthelper.exe

cthelper.exe: $(OBJ)
	#$(q) $(LINK) $(LDFLAGS) -o $@ $(OBJ) $(LDLIBS)
#cthelper.o: cthelper.c cthelper.h ptyfork.h buffer.h debug.h
buffer.o: buffer.c buffer.h debug.h
message.o: message.c message.h debug.h
.c.o:; $(q) $(CC) $(CFLAGS) -o $@ -c $*.c

checkin: Makefile $(SRC)
	ci -l $^

TAGS: $(SRC)
	ctags $^
clean:
	rm -f *.o *.exe *~ *.stackdump *core tags

