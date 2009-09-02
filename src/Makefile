PROG        = liqbase-playground
VERS        = 0.1.0
CC          = gcc
LD          = gcc


OPT_FLAGS   =  -O3
DESTDIR	?= tmp

LIBRARIES   =
# xrandr
# -DUSE_MAEMO 
CFLAGS      = -DUSE_MAEMO -Wall   -I/usr/include `pkg-config --cflags  $(LIBRARIES)` 
LDFLAGS     = -lm -lliqbase `pkg-config --libs $(LIBRARIES)`  -lpthread  -Wl,-export-dynamic -L/usr/local/lib

RM          = /bin/rm -f

OBJSCORE    = playground.o desktopmanage.o
OBJS        = $(OBJSCORE) $(PROG).o




.PHONY:     clean distclean
all:        $(PROG)
	      $(MAKE) -C widgets

$(PROG):    $(OBJS)
	      $(LD) $(LDFLAGS) -o $(PROG) $(OBJS) \
		
.c.o:
	      $(CC) $(OPT_FLAGS) $(CFLAGS) -c $< -o $*.o
clean:
	      $(RM) *~ $(OBJS) $(PROG)
		$(MAKE) clean -C widgets

.PHONY:     clean

