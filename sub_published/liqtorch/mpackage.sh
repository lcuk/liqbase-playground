#!/bin/sh
# build a package
# by lcuk on #maemo  liquid@gmail.com

find . -print0 | xargs -r0 touch
chmod +x debian/rules
fakeroot dpkg-buildpackage -i -I.git


# for updating from scratchbox to my personal device
scp ../liqtorch_0.1.6_armel.deb root@10.0.0.8:/root/liqtorch_0.1.6_armel.deb
ssh root@10.0.0.8 "dpkg -i liqtorch_0.1.6_armel.deb"

