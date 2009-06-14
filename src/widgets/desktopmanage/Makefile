PROG        = desktopmanage
VERS        = 0.1.0
CC          = gcc
LD          = gcc

OPT_FLAGS   =  -O3

LIBRARIES   = 

CFLAGS      = $(OPT_FLAGS) -DUSE_MAEMO -Wall  -I../../../include -I../
LDFLAGS     = -lm -lliqbase
RM          = /bin/rm -f



SRCS        = $(wildcard *.c)

OBJS        = $(patsubst %.c,%.o,$(SRCS))

LIBS        = $(patsubst %.c,%.so,$(SRCS))

BINS        = $(patsubst %.c,%,$(SRCS))

.PHONY:     clean distclean

all:        $(PROG).so


%.o : %.c
	$(CC) -c -fpic $(CFLAGS) $(CPPFLAGS) $< -o $@

$(PROG).so : $(OBJS)
	$(LD) -shared -lc $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(PROG).so


clean:
	      $(RM) *~ $(OBJS) $(PROG).so

.PHONY:     clean



