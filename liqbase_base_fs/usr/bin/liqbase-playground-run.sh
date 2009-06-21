#!/bin/sh
# make and run
# by lcuk on #maemo  liquid@gmail.com

export DISPLAY=:0.0

sudo liqbase-playground-cpu-performance

cd /usr/share/liqbase

./liqbase-playground -showwidget kotcomix,tagcloud,liqcontrolpanel,liqcalendar,ciroclock_minutes,liqtop,liqrecentsketches,liqrecentusers,liqbook

sudo liqbase-playground-cpu-ondemand





