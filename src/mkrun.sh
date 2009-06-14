#!/bin/sh
# make and run
# by lcuk on #maemo  liquid@gmail.com

export DISPLAY=:0.0

cd /home/user/svn/liqbase-playground/src

if make; 
	then ./liqbase-playground;
fi




