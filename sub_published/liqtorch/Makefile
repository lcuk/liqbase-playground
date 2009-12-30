PROG = liqtorch

VERS		  = 0.1.0
ETCDIR		= $(DESTDIR)/etc
PREFIX		= $(DESTDIR)/usr
cc = gcc
LD = gcc
OPT_FLAGS = -O3
CFLAGS		= -g
LDFLAGS	  = -lm -lliqbase -Wl,-export-dynamic
RM			 = /bin/rm -f
OBJSCORE	 = liqtorch_run.o
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
			 install -d								 $(PREFIX)/share/liqbase/liqtorch
			 install -d								 $(PREFIX)/share/liqbase/liqtorch/media


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


	install -m 0755  base_fs/usr/share/icons/hicolor/26x26/apps/liqtorch.png 				$(PREFIX)/share/icons/hicolor/26x26/apps/liqtorch.png
	install -m 0755  base_fs/usr/share/icons/hicolor/48x48/apps/liqtorch.png 				$(PREFIX)/share/icons/hicolor/48x48/apps/liqtorch.png
	install -m 0755  base_fs/usr/share/icons/hicolor/scalable/apps/liqtorch.png 				$(PREFIX)/share/icons/hicolor/scalable/apps/liqtorch.png
			 
			 mkdir -p									$(PREFIX)/share/liqbase
			 mkdir -p									$(PREFIX)/share/liqbase/liqtorch/media
			 
			 install -m 0755 liqtorch			  $(PREFIX)/share/liqbase/liqtorch
			 install -m 0755 liqtorch.so		  $(PREFIX)/share/liqbase/liqtorch
			 
			 install -m 0755 base_fs/usr/bin/liqtorch-run.sh										 $(PREFIX)/bin
			 install -m 0755 base_fs/usr/share/applications/hildon/liqtorch.desktop		  $(PREFIX)/share/applications/hildon
			 install -m 0755 base_fs/usr/share/dbus-1/services/org.maemo.liqtorch.service  $(PREFIX)/share/dbus-1/services
			 install -m 0755 base_fs/etc/osso-backup/applications/liqtorch.conf				$(ETCDIR)/osso-backup/applications
			 
			 
			 
			 
			 
			 
			 
			 
			 
			 
			 
