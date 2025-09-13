#!/bin/sh
for i in $(seq 1 30); do
    val=$((i))
    sbatch omp-llc.sh 1024 $val
done

for i in $(seq 1 30); do
    val2=$((i))
    sbatch row-llc.sh 1024 $val2
done