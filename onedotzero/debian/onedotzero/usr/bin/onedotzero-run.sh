#!/bin/sh
# make and run
# by lcuk on #maemo  liquid@gmail.com

export DISPLAY=:0.0


if [ ` grep "cpuboost=0" /home/user/.liqbase/liqbase.prefs 2>/dev/null` ];
then 
	echo "liqbase-no_cpuboost"
else
	if [ `whoami` != 'root' ];
	then
		sudo /usr/bin/liqbase-playground-cpu-performance;
	else
		/usr/bin/liqbase-playground-cpu-performance;
	fi	
fi



cd /usr/share/liqbase/onedotzero


	./onedotzero


if [ ` grep "cpuboost=0" /home/user/.liqbase/liqbase.prefs 2>/dev/null` ];
then 
	echo "liqbase-no_cpuboost"; 
else
	if [ `whoami` != 'root' ];
	then
		sudo /usr/bin/liqbase-playground-cpu-ondemand;
	else
		/usr/bin/liqbase-playground-cpu-ondemand;
	fi
fi
