PROG = invar

VERS		  = 0.1.0
ETCDIR		= $(DESTDIR)/etc
PREFIX		= $(DESTDIR)/usr
cc = gcc
LD = gcc
OPT_FLAGS = -O3
CFLAGS		= 
LDFLAGS	  = -lm -lliqbase -Wl,-export-dynamic
RM			 = /bin/rm -f
OBJSCORE	 = invar_calibrate.o invar_config.o invar_host.o invar_rawview.o invar_run.o liqbase_about.o
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
			 install -d								 $(PREFIX)/share/liqbase/invar
			 install -d								 $(PREFIX)/share/liqbase/invar/media
			 
			 mkdir -p									$(PREFIX)/share/liqbase
			 mkdir -p									$(PREFIX)/share/liqbase/invar/media
			 
			 install -m 0755 invar			  $(PREFIX)/share/liqbase/invar
			 install -m 0755 invar.so		  $(PREFIX)/share/liqbase/invar
			 
			 cp -r media/*							 $(PREFIX)/share/liqbase/invar/media
			 
			 install -m 0755 base_fs/usr/bin/invar-run.sh										 $(PREFIX)/bin
			 install -m 0755 base_fs/usr/share/applications/hildon/invar.desktop		  $(PREFIX)/share/applications/hildon
			 install -m 0755 base_fs/usr/share/dbus-1/services/org.maemo.invar.service  $(PREFIX)/share/dbus-1/services
			 install -m 0755 base_fs/etc/osso-backup/applications/invar.conf				$(ETCDIR)/osso-backup/applications
			 mkdir -p																				$(PREFIX)
			 mkdir -p																				$(PREFIX)/share
			 mkdir -p																				$(PREFIX)/share/icons
			 mkdir -p																				$(PREFIX)/share/icons/hicolor
			 mkdir -p																				$(PREFIX)/share/icons/hicolor/scalable
			 mkdir -p																				$(PREFIX)/share/icons/hicolor/scalable/apps
			 install -m 0755  invar.png													$(PREFIX)/share/icons/hicolor/scalable/apps/invar.png
			 
			 
			 
			 
			 
			 
			 
			 
			 
			 
			 