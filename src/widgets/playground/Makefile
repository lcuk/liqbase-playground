PROG = playground
VERS		  = 0.1.0
cc = gcc
LD = gcc
OPT_FLAGS = -O3
CFLAGS		= -I../../../include
LDFLAGS	  = -lm -lliqbase -Wl,-export-dynamic  -lpthread  
RM			 = /bin/rm -f
OBJSCORE	 = textbox.o tagcloud.o recentsketches.o recentpictures.o booklist.o songlist.o codelist.o 
OBJS		  = $(OBJSCORE) $(PROG).o
.PHONY:	  clean distclean
all:		  $(PROG) $(PROG).so
$(PROG):	 $(OBJS)
			 $(LD) $(LDFLAGS) -o $(PROG) $(OBJS)
$(PROG).so : $(OBJS)
	 $(LD) -shared -lc $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(PROG).so
.c.o:
			 $(CC) $(OPT_FLAGS) $(CFLAGS) -c $< -o $*.o
clean:
			 $(RM) *~ $(OBJS) $(PROG) $(PROG).so
.PHONY:	  clean
