#!/bin/sh
# make and run
# by lcuk on #maemo  liquid@gmail.com

export DISPLAY=:0.0


if [ ` grep "cpuboost=0" /home/user/.liqbase/liqbase.prefs 2>/dev/null` ];
then 
	echo "liqbase-no_cpuboost"
else
	if [ -e "/usr/bin/liqbase-playground-cpu-performance" ]
	then
	    sudo /usr/bin/liqbase-playground-cpu-performance
	fi
fi



cd /usr/share/liqbase/liqcalendar


	./liqcalendar


if [ ` grep "cpuboost=0" /home/user/.liqbase/liqbase.prefs 2>/dev/null` ];
then 
	echo "liqbase-no_cpuboost"; 
else
	if [ -e "/usr/bin/liqbase-playground-cpu-ondemand" ]
	then
	    sudo /usr/bin/liqbase-playground-cpu-ondemand
	fi
fi
