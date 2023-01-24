#!/bin/bash

getData() {
    CPUTEMP=$(sensors -j | jq '."coretemp-isa-0000" | ."Package id 0" | ."temp1_input"')
    GPUTEMP=$(nvidia-smi -q -d temperature | awk 'FNR == 10 {print}')
    MEM=$(free -h | awk '{print $3, $2}' | awk "NR == 2")
    CPU=$(top -bn1 | grep "Cpu(s)" | sed "s/.*, *\([0-9.]*\)%* id.*/\1/" | awk '{print 100 - $1"%"}')
    echo "{\"CPU\": \"$CPU\", \"MEM\": \"$MEM\", \"CPU_TEMP\": $CPUTEMP, \"GPU_TEMP\": \"$GPUTEMP\"}" >/home/paulyurlov/serv_mon/data.json
}

while :; do
    getData
done
