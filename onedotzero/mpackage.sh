#!/bin/sh
# build a package
# by lcuk on #maemo  liquid@gmail.com

find . -print0 | xargs -r0 touch
chmod +x debian/rules
fakeroot dpkg-buildpackage -i -I.git
