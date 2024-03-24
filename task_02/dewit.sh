#!/bin/sh

set +eux

compile()
{
    IN=$1
    OUT=$2
    gcc -fopenmp $IN -o $OUT
}

compile pi_para.c para.out
compile pi_normal.c no_para.out
