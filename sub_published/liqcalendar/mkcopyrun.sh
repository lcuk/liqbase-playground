#!/bin/sh
# make and copy and run
# by lcuk on #maemo  liquid@gmail.com

if make; then 
  scp -r ./liqcalendar ./liqcalendar.so media root@10.0.0.8:/usr/share/liqbase/liqcalendar
  ssh root@10.0.0.8 "export DISPLAY=:0.0; liqcalendar-run.sh"
  #ssh root@10.0.0.8 "killall -9 liqcalendar
fi

