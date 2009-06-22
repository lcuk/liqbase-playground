#!/bin/sh
# make and run
# by lcuk on #maemo  liquid@gmail.com

export DISPLAY=:0.0

sudo liqbase-playground-cpu-performance

cd /usr/share/liqbase

# YES, this is a hack, i dunno the right way though :)
# just make sure this is only run on n8x0

 MAEMO_SELECT_MENU=/usr/bin/maemo-select-menu-location
 if [ -f $MAEMO_SELECT_MENU ]
 then

   ./liqbase-playground -showwidget tagcloud,liqcontrolpanel,liqcalendar,ciroclock_minutes,liqtop,liqrecentsketches,liqrecentusers,liqbook
 else
   ./liqbase-playground -showwidget tagcloud,liqcontrolpanel,liqcalendar,ciroclock_minutes,liqtop,liqrecentsketches,liqrecentusers,liqbook,liqaccelview

 fi

sudo liqbase-playground-cpu-ondemand





