#!/bin/sh
# make and run
# by lcuk on #maemo  liquid@gmail.com


cd ..

./mkrun.sh

cd playground

if make; then ./playground; fi



