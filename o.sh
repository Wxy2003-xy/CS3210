#!/bin/sh
for i in $(seq 1 30); do
    val=$((i))
    sbatch omp-job.sh 1024 $val
done

# for i in $(seq 1 30); do
#     val=$((i))
#     sbatch row-job.sh 1024 $val
# done
