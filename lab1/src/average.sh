#!/bin/bash
count=0
avg=0
for param in "$@"
do
avg=$(($param + avg))
count=$(( $count + 1 ))
done
avg=$((avg/count))
echo "Количество $count"
echo "Среднее $avg"