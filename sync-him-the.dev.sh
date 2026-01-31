#!/bin/bash

read -p "want to sync him to you? it could revert much of your work" answer
case $answer in
[yY]* ) echo "syncing him to you" rsync -av --delete poklop@192.168.1.110:/home/poklop/77/telefonni_centrala_na_rohu_77 ..;;
[nN]* ) echo "end 1";;
[cC]* ) echo "end";;
* ) ;;
esac