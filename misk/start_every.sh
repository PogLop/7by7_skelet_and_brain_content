#!/bin/bash

kudy="/home/poklop/77/telefonni_centrala_na_rohu_77"

sudo $kudy/main.o &
sudo puredata -nogui -audiooutdev 0 -noadc -rt -blocksize 16 -audiobuf 32 $kudy/pd/osc_test.pd