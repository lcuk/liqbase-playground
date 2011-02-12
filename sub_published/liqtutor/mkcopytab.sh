#!/bin/bash
# make and run
# by lcuk on #maemo  liquid@gmail.com
if make; then
 scp liqtutor liqtutor.so root@10.0.0.8:/usr/share/liqbase/liqtutor; 
 #ssh root@10.0.0.8 liqtactoe-run.sh;
fi;


