PROG = liqcontrolpanel

VERS		  = 0.1.0
ETCDIR		= $(DESTDIR)/etc
PREFIX		= $(DESTDIR)/usr
cc = gcc
LD = gcc
OPT_FLAGS = -O3
CFLAGS		= 
LDFLAGS	  = -lm -lliqbase -Wl,-export-dynamic
RM			 = /bin/rm -f
OBJSCORE	 = liqbrightness.o liqmemory.o liqbattery.o liqcpu.o
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
			 install -d								 $(PREFIX)/share/liqbase/liqcontrolpanel
			 install -d								 $(PREFIX)/share/liqbase/liqcontrolpanel/media
			 
			 mkdir -p									$(PREFIX)/share/liqbase
			 mkdir -p									$(PREFIX)/share/liqbase/liqcontrolpanel/media
			 
			 install -m 0755 liqcontrolpanel			  $(PREFIX)/share/liqbase/liqcontrolpanel
			 install -m 0755 liqcontrolpanel.so		  $(PREFIX)/share/liqbase/liqcontrolpanel
			 
			 cp -r media/*							 $(PREFIX)/share/liqbase/liqcontrolpanel/media
			 
			 install -m 0755 base_fs/usr/bin/liqcontrolpanel-run.sh										 $(PREFIX)/bin
			 install -m 0755 base_fs/usr/share/applications/hildon/liqcontrolpanel.desktop		  $(PREFIX)/share/applications/hildon
			 install -m 0755 base_fs/usr/share/dbus-1/services/org.maemo.liqcontrolpanel.service  $(PREFIX)/share/dbus-1/services
			 install -m 0755 base_fs/etc/osso-backup/applications/liqcontrolpanel.conf				$(ETCDIR)/osso-backup/applications
			 
			 
			 
			 
			 
			 
			 
			 
			 
			 
			 