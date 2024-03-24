#!/bin/sh

set +eux

compile()
{
    IN=$1
    OUT=$2
    gcc -fopenmp $IN -o $OUT
}

compile pi_minimal.c minimal.out
