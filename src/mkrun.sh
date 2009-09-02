#!/bin/sh
# make and run
# by lcuk on #maemo  liquid@gmail.com

export DISPLAY=:0.0

#cd /home/user/svn/libliqbase-0.3/
#if make; 
#	then sudo make install; 
#fi
#cd /home/user/svn/liqbase-playground/src

if make; 
	#then ./liqbase-playground -showwidget liqdesign,tagcloud,liqcontrolpanel,liqcalendar,ciroclock_minutes,liqtop,liqrecentsketches,liqrecentusers,liqbook,liqaccelview_angle;

	then ./liqbase-playground -showwidget desktopmanage,liqstarspull,liqrecentphotos,liqcalendar,ciroclock_minutes,liqtop,liqrecentsketches,liqaccelview;


	#then ./liqbase-playground -showwidget liqdesign,liqcalendar,ciroclock_minutes,liqtop,liqrecentsketches,liqstarspull,liqrecentphotos;


fi




