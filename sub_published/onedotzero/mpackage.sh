#!/bin/sh
# build a package
# by lcuk on #maemo  liquid@gmail.com

find . -print0 | xargs -r0 touch
chmod +x debian/rules
dpkg-buildpackage -rfakeroot -i -I.git
# for updating from 810
 scp ../onedotzero_1.0.2_armel.deb root@10.0.0.8:~
 ssh root@10.0.0.8 "dpkg -i onedotzero_1.0.2_armel.deb"
 
