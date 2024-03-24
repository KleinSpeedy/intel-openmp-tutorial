#!/bin/sh

set +eux

compile()
{
    IN=$1
    OUT=$2
    gcc -fopenmp $IN -o $OUT
}

compile pi_para_no_sharing.c solution.out
