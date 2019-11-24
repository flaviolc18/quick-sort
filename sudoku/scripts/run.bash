#!/bin/bash

if [ "$#" -ne 1 ]; then
  echo "usage: bash benchmark.sh [executable]"
  exit 2
fi

if [ ! -x $1 ]; then
  echo "invalid executable $1"
  exit 2
fi

BASEDIR=$(pwd)
INDIR="$BASEDIR/test/dataset2/in"
OUTDIR="$BASEDIR/test/dataset2/out"

for FILENAME in $(ls $INDIR); do
    ts=$(date +%s%N)
    $($1 $INDIR/$FILENAME > $OUTDIR/$FILENAME)
    elapsed=$((($(date +%s%N) - $ts) / 1000))
    echo $elapsed
done
