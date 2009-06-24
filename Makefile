PROG        = liqbase-playground
VERS        = 0.3.0
CC          = gcc
LD          = gcc


OPT_FLAGS   =  -O3
#DESTDIR	?= tmp


ETCDIR	    = $(DESTDIR)/etc
PREFIX	    = $(DESTDIR)/usr
SUDODIR	    = $(ETCDIR)/sudoers.d
BINDIR	    = $(PREFIX)/bin
DESKTOPDIR      = $(PREFIX)/share/applications/hildon
SERVICEDIR      = $(PREFIX)/share/dbus-1/services
PGDIR		    = $(PREFIX)/share/liqbase


.PHONY:     clean distclean
all:        
	$(MAKE) -C src

clean:
	      $(MAKE) clean -C src

.PHONY:     clean

install:

	install -d $(BINDIR)
	install -d $(SUDODIR)
	install -d $(DESKTOPDIR)
	install -d $(SERVICEDIR)
	install -d $(PGDIR)

	mkdir -p                                    									$(PGDIR)
	mkdir -p                                    									$(PGDIR)/media
	mkdir -p                                    									$(PGDIR)/kotcomix
	mkdir -p                                    									$(PGDIR)/dialogfileselect
	mkdir -p                                    									$(PGDIR)/widgets
	mkdir -p                                    									$(PGDIR)/widgets/liqcalendar
	mkdir -p                                    									$(PGDIR)/widgets/playground
	mkdir -p                                    									$(PGDIR)/widgets/desktopmanage
	mkdir -p                                    									$(PGDIR)/liqbook

	cp -r src/media/*                           									$(PGDIR)/media
	#cp -r src/widgets/media/*                  									 $(PGDIR)/media
	#cp -r src/widgets/liqcalendar/media/*      									 $(PGDIR)/media
	#cp -r src/widgets/playground/media/*       									 $(PGDIR)/media
	#cp -r src/liqbook/media/*      		    									 $(PGDIR)/media
	#cp -r src/widgets/desktopmanage/media/*    									 $(PGDIR)/media

	install -m 0755 src/liqbase-playground      									$(PGDIR)
	install -m 0755 src/kotcomix/kotcomix      									$(PGDIR)/kotcomix
	cp -r src/widgets/*.so                      									$(PGDIR)/widgets
	cp -r src/widgets/liqcalendar/*.so          									$(PGDIR)/widgets/liqcalendar
	cp -r src/widgets/playground/*.so           									$(PGDIR)/widgets/playground
	cp -r src/widgets/desktopmanage/*.so        									$(PGDIR)/widgets/desktopmanage
	cp -r src/liqbook/*.so     		         									$(PGDIR)/liqbook
	cp -r src/kotcomix/kotcomix.so              									$(PGDIR)/kotcomix
	cp -r src/dialogfileselect/dialogfileselect.so        							$(PGDIR)/dialogfileselect



	install -m 0755 liqbase_base_fs/usr/bin/liqbase-playground-run.sh                               $(BINDIR)
	install -m 0755 liqbase_base_fs/usr/bin/liqbase-playground-cpu-ondemand                         $(BINDIR)
	install -m 0755 liqbase_base_fs/usr/bin/liqbase-playground-cpu-powersave                        $(BINDIR)
	install -m 0755 liqbase_base_fs/usr/bin/liqbase-playground-cpu-performance                      $(BINDIR)
	install -m 0755 liqbase_base_fs/etc/sudoers.d/liqbase-playground.sudoers                        $(SUDODIR)
	install -m 0755 liqbase_base_fs/usr/share/applications/hildon/liqbase_playground.desktop        $(DESKTOPDIR)
	install -m 0755 liqbase_base_fs/usr/share/dbus-1/services/org.maemo.liqbase_playground.service  $(SERVICEDIR)

	install -m 0755 liqbase_base_fs/etc/osso-backup/applications/liqbase-playground.conf            $(ETCDIR)/osso-backup/applications


