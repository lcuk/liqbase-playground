#!/bin/sh
# make and run
# by lcuk on #maemo  liquid@gmail.com

export DISPLAY=:0.0


if [ ` grep "cpuboost=0" /home/user/.liqbase/liqbase.prefs 2>/dev/null` ];
then 
	echo "liqbase-no_cpuboost"
else
	sudo /usr/bin/liqbase-playground-cpu-performance
fi



cd /usr/share/liqbase/invar


	./invar


if [ ` grep "cpuboost=0" /home/user/.liqbase/liqbase.prefs 2>/dev/null` ];
then 
	echo "liqbase-no_cpuboost"; 
else
	sudo /usr/bin/liqbase-playground-cpu-ondemand
fi
