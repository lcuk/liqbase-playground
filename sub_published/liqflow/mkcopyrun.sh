#!/bin/sh
# make and copy and run
# by lcuk on #maemo  liquid@gmail.com

if make; then 
  scp -r ./liqflow ./liqflow.so media root@10.0.0.8:/usr/share/liqbase/liqflow
  ssh root@10.0.0.8 "export DISPLAY=:0.0; liqflow-run.sh
  #ssh root@10.0.0.8 "killall -9 liqflow
fi
