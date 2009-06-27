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



cd /usr/share/liqbase

# thank you qwerty12 and kotczarny
# just make sure this is only run on n8x0
if [ -e /proc/component_version ];
then
 HW_VER=`awk '/^product/ { print $2;}' /proc/component_version | cut -d- -f2`
else
 HW_VER="0"
fi

 if [ "$HW_VER" -ge "34" -a "$HW_VER" -le "48" ];
 then

   ./liqbase-playground -showwidget tagcloud,liqcontrolpanel,liqcalendar,ciroclock_minutes,liqtop,liqrecentsketches,liqrecentusers,liqbook
 else
   ./liqbase-playground -showwidget tagcloud,liqcontrolpanel,liqcalendar,ciroclock_minutes,liqtop,liqrecentsketches,liqrecentusers,liqbook,liqaccelview
 fi




if [ ` grep "cpuboost=0" /home/user/.liqbase/liqbase.prefs 2>/dev/null` ];
then 
	echo "liqbase-no_cpuboost"; 
else
	sudo /usr/bin/liqbase-playground-cpu-ondemand
fi


