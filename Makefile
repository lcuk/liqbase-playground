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
	mkdir -p                                    									$(PGDIR)/widgets
	mkdir -p                                    									$(ETCDIR)
	mkdir -p                                    									$(ETCDIR)/osso-backup
	mkdir -p                                    									$(ETCDIR)/osso-backup/applications



	mkdir -p															$(PREFIX)
	mkdir -p															$(PREFIX)/share
	mkdir -p															$(PREFIX)/share/icons
	mkdir -p															$(PREFIX)/share/icons/hicolor
	mkdir -p															$(PREFIX)/share/icons/hicolor/scalable
	mkdir -p															$(PREFIX)/share/icons/hicolor/scalable/apps


	cp -r media/*       	                    									$(PGDIR)/media

	install -m 0755 src/liqbase-playground      									$(PGDIR)
	cp -r src/widgets/*.so                      									$(PGDIR)/widgets


	install -m 0755 liqbase_base_fs/usr/bin/liqbase-playground-run.sh                               $(BINDIR)
	install -m 0755 liqbase_base_fs/usr/bin/liqbase-playground-cpu-ondemand                         $(BINDIR)
	install -m 0755 liqbase_base_fs/usr/bin/liqbase-playground-cpu-powersave                        $(BINDIR)
	install -m 0755 liqbase_base_fs/usr/bin/liqbase-playground-cpu-performance                      $(BINDIR)
	install -m 0755 liqbase_base_fs/etc/sudoers.d/liqbase-playground.sudoers                        $(SUDODIR)
	install -m 0755 liqbase_base_fs/usr/share/applications/hildon/liqbase_playground.desktop        $(DESKTOPDIR)
	install -m 0755 liqbase_base_fs/usr/share/dbus-1/services/org.maemo.liqbase_playground.service  $(SERVICEDIR)
	install -m 0755 liqbase_base_fs/etc/osso-backup/applications/liqbase-playground.conf            $(ETCDIR)/osso-backup/applications

	install -m 0755 liqbase_base_fs/usr/share/icons/hicolor/scalable/apps/liqbase_playground.png    $(PREFIX)/share/icons/hicolor/scalable/apps/liqbase_playground.png



