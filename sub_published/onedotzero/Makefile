PROG = onedotzero
VERS		  = 0.1.0
ETCDIR		= $(DESTDIR)/etc
PREFIX		= $(DESTDIR)/usr
cc = gcc
LD = gcc
OPT_FLAGS = -O3
LIBRARIES   = sqlite3 liblo
CFLAGS		= -Wall `pkg-config --cflags  $(LIBRARIES)`  
LDFLAGS	  = -lm -lliqbase -Wl,-export-dynamic -lcurl -L /usr/lib `pkg-config --libs $(LIBRARIES)`
RM			 = /bin/rm -f
OBJSCORE	 = onemessage.o onemessageprogress.o textbox.o onetilt.o zoombox.o oneconfigure.o buttonrollover.o onemenu.o nokiapicture.o onemove.o osc_onedotzero.o 
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



			 install -d								 $(PREFIX)/share/liqbase/onedotzero
			 install -d								 $(PREFIX)/share/liqbase/onedotzero/media




	mkdir -p															$(PREFIX)
	mkdir -p															$(PREFIX)/share
	mkdir -p															$(PREFIX)/share/icons
	mkdir -p															$(PREFIX)/share/icons/hicolor
	mkdir -p															$(PREFIX)/share/icons/hicolor/scalable
	mkdir -p															$(PREFIX)/share/icons/hicolor/scalable/apps


			 cp base_fs/usr/share/icons/hicolor/scalable/apps/onedotzero_icon.png   $(PREFIX)/share/icons/hicolor/scalable/apps

			 
			 mkdir -p									$(PREFIX)/share/liqbase
			 mkdir -p									$(PREFIX)/share/liqbase/onedotzero
			 mkdir -p									$(PREFIX)/share/liqbase/onedotzero/media
			 
			 install -m 0755 onedotzero			  $(PREFIX)/share/liqbase/onedotzero
			 install -m 0755 onedotzero.so		  $(PREFIX)/share/liqbase/onedotzero
			 cp -r media/*                           				$(PREFIX)/share/liqbase/onedotzero/media

			 install -m 0755 base_fs/usr/bin/onedotzero-run.sh										 $(PREFIX)/bin
			 install -m 0755 base_fs/usr/share/applications/hildon/onedotzero.desktop		  $(PREFIX)/share/applications/hildon
			 install -m 0755 base_fs/usr/share/dbus-1/services/org.maemo.onedotzero.service  $(PREFIX)/share/dbus-1/services
			 install -m 0755 base_fs/etc/osso-backup/applications/onedotzero.conf				$(ETCDIR)/osso-backup/applications
			 
