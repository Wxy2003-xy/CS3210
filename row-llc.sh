#!/bin/bash
#SBATCH --job-name=lab2-mmomp
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --partition=i7-7700
#SBATCH --mem=1gb
#SBATCH --time=00:03:00
#SBATCH --open-mode=append
#SBATCH --output=mmomp_i7_mem.slurmlog
#SBATCH --mail-type=NONE

srun g++ -fopenmp -o mm-omp mm-omp.cpp -O3
srun perf stat -r 3 \
  -e fp_arith_inst_retired.scalar_single,\
L1-dcache-load-misses,\
LLC-load-misses,\
dTLB-load-misses \
  ./mm-omp $@
