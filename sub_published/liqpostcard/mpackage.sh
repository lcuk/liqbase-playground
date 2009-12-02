#!/bin/sh
# build a package
# by lcuk on #maemo  liquid@gmail.com

find . -print0 | xargs -r0 touch
chmod +x debian/rules
dpkg-buildpackage -rfakeroot -i -I.git
# for updating from 810
# scp gary@10.0.0.10:/scratchbox/users/gary/home/gary/svn/liqpostcard_0.1.0_armel.deb ~
# dpkg -i liqpostcard_0.1.0_armel.deb