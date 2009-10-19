PROG = maemosummit2009

VERS		  = 0.1.0
ETCDIR		= $(DESTDIR)/etc
PREFIX		= $(DESTDIR)/usr
cc = gcc
LD = gcc
OPT_FLAGS = -O3

LIBRARIES   = liblo
CFLAGS		= -Wall `pkg-config --cflags  $(LIBRARIES)`  
LDFLAGS	  = -lm -lliqbase -Wl,-export-dynamic -L /usr/lib `pkg-config --libs $(LIBRARIES)`
RM			 = /bin/rm -f
OBJSCORE	 = liqslidehost.o liqpages.o vbparse.o osc_maemosummit.o 
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

install:
			 install -d								 $(ETCDIR)/osso-backup
			 install -d								 $(ETCDIR)/osso-backup/applications
			 install -d								 $(PREFIX)/bin
			 install -d								 $(PREFIX)/share/applications/hildon
			 install -d								 $(PREFIX)/share/dbus-1/services
			 install -d								 $(PREFIX)/share/liqbase
			 install -d								 $(PREFIX)/share/liqbase/maemosummit2009
			 install -d								 $(PREFIX)/share/liqbase/maemosummit2009/media
			 
			 mkdir -p									$(PREFIX)/share/liqbase
			 mkdir -p									$(PREFIX)/share/liqbase/maemosummit2009/media
			 
			 install -m 0755 maemosummit2009			  $(PREFIX)/share/liqbase/maemosummit2009
			 install -m 0755 maemosummit2009.so		  $(PREFIX)/share/liqbase/maemosummit2009
			 
			 cp -r media/*							 $(PREFIX)/share/liqbase/maemosummit2009/media
			 
			 install -m 0755 base_fs/usr/bin/maemosummit2009-run.sh										 $(PREFIX)/bin
			 install -m 0755 base_fs/usr/share/applications/hildon/maemosummit2009.desktop		  $(PREFIX)/share/applications/hildon
			 install -m 0755 base_fs/usr/share/dbus-1/services/org.maemo.maemosummit2009.service  $(PREFIX)/share/dbus-1/services
			 install -m 0755 base_fs/etc/osso-backup/applications/maemosummit2009.conf				$(ETCDIR)/osso-backup/applications
			 
			 
			 
			 
			 
			 
			 
			 
			 
			 
			 
