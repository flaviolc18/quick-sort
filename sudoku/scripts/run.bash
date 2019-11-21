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
INDIR="$BASEDIR/test/dataset/in"
OUTDIR="$BASEDIR/test/dataset/out"

for FILENAME in $(ls $INDIR); do
  $($1 < $INDIR/$FILENAME > $OUTDIR/$FILENAME)
done
