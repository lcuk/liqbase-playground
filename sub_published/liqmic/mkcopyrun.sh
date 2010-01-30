#!/bin/sh
# make and copy and run
# by lcuk on #maemo  liquid@gmail.com

if make; then 
  scp -r ./liqmic ./liqmic.so media root@10.0.0.8:/usr/share/liqbase/liqmic
  ssh root@10.0.0.8 "export DISPLAY=:0.0; liqmic-run.sh
  ssh root@10.0.0.8 "killall -9 liqmic
fi
