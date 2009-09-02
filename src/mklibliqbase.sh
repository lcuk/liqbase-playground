#!/bin/sh
# make and install libliqbase
# by lcuk on #maemo  liquid@gmail.com

export DISPLAY=:0.0

cd /home/user/svn/libliqbase-0.3/
if make; 
	then make install; 
fi

