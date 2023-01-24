#!/bin/bash

sensors -j >info.json
MEM=$(free -h | awk '{print $3, $2}' | awk "NR == 2")
CPU=$(top -bn1 | grep "Cpu(s)" | sed "s/.*, *\([0-9.]*\)%* id.*/\1/" | awk '{print 100 - $1"%"}')
echo "{\"CPU\": \"$CPU\", \"MEM\": \"$MEM\"}" >cpu_mem.json
