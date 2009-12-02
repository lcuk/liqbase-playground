#!/bin/sh
# make and run
# by lcuk on #maemo  liquid@gmail.com



cd /home/user/svn/onedotzero

if make; then ./onedotzero; fi
# build a package with:
#dpkg-buildpackage -rfakeroot -i -I.git