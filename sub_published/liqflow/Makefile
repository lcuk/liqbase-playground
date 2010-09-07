PROG = liqflow

VERS		  = 0.1.0
ETCDIR		= $(DESTDIR)/etc
PREFIX		= $(DESTDIR)/usr
cc = gcc
LD = gcc
OPT_FLAGS = -O3
CFLAGS		= -I/usr/include/dbus-1.0 -I/usr/lib/dbus-1.0/include
LDFLAGS	  = -lm -lliqbase -Wl,-export-dynamic -ldbus-1
RM			 = /bin/rm -f
OBJSCORE	 = liqflow_cover.o liqflow_run.o liqflow_config.o
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
			 install -d								 $(PREFIX)/share/liqbase/liqflow
			 install -d								 $(PREFIX)/share/liqbase/liqflow/media
			 
			 mkdir -p									$(PREFIX)/share/liqbase
			 mkdir -p									$(PREFIX)/share/liqbase/liqflow/media

	mkdir -p															$(PREFIX)
	mkdir -p															$(PREFIX)/share
	mkdir -p															$(PREFIX)/share/icons
	mkdir -p															$(PREFIX)/share/icons/hicolor
	mkdir -p															$(PREFIX)/share/icons/hicolor/scalable
	mkdir -p															$(PREFIX)/share/icons/hicolor/scalable/apps
	mkdir -p															$(PREFIX)/share/icons/hicolor/26x26
	mkdir -p															$(PREFIX)/share/icons/hicolor/26x26/apps
	mkdir -p															$(PREFIX)/share/icons/hicolor/48x48
	mkdir -p															$(PREFIX)/share/icons/hicolor/48x48/apps

	install -m 0755  base_fs/usr/share/icons/hicolor/26x26/apps/liqflow.png 				$(PREFIX)/share/icons/hicolor/26x26/apps/liqflow.png
	install -m 0755  base_fs/usr/share/icons/hicolor/48x48/apps/liqflow.png 				$(PREFIX)/share/icons/hicolor/48x48/apps/liqflow.png
	install -m 0755  base_fs/usr/share/icons/hicolor/scalable/apps/liqflow.png 				$(PREFIX)/share/icons/hicolor/scalable/apps/liqflow.png

			 
			 install -m 0755 liqflow			  $(PREFIX)/share/liqbase/liqflow
			 install -m 0755 liqflow.so		  $(PREFIX)/share/liqbase/liqflow
			 
			 cp -r media/*							 $(PREFIX)/share/liqbase/liqflow/media
			 
			 install -m 0755 base_fs/usr/bin/liqflow-run.sh										 $(PREFIX)/bin
			 install -m 0755 base_fs/usr/share/applications/hildon/liqflow.desktop		  $(PREFIX)/share/applications/hildon
			 install -m 0755 base_fs/usr/share/dbus-1/services/org.maemo.liqflow.service  $(PREFIX)/share/dbus-1/services
			 install -m 0755 base_fs/etc/osso-backup/applications/liqflow.conf				$(ETCDIR)/osso-backup/applications
			 
			 
			 
			 
			 
			 
			 
			 
			 
			 
			 
