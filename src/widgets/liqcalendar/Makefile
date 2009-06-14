PROG        = liqcalendar
VERS        = 0.1.0
CC          = gcc
LD          = gcc
OPT_FLAGS   =  -O3
LDFLAGS     = -lm -lliqbase -Wl,-export-dynamic  -ldl  -lpthread  
RM          = /bin/rm -f
CFLAGS      = -fPIC
OBJSCORE    = liqui_toolbar.o liqcalendar_dayview.o
OBJS        = $(OBJSCORE) $(PROG).o 
.PHONY:     clean distclean
all:        $(PROG) $(PROG).so
$(PROG):    $(OBJS)
	      $(LD) $(LDFLAGS) -o $(PROG) $(OBJS)
$(PROG).so : $(OBJS)
	$(LD) -shared -lc $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(PROG).so
.c.o:
	      $(CC) $(OPT_FLAGS) $(CFLAGS) -c $< -o $*.o
clean:
	      $(RM) *~ $(OBJS) $(PROG) $(PROG).so
.PHONY:     clean

