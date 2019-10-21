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
SCRIPTDIR="$BASEDIR/scripts"
TESTDIR="$BASEDIR/test"
TESTFILE="$TESTDIR/t.txt"
LOGFILE="$TESTDIR/log.json"

mkdir -p $TESTDIR

echo "runnig benchmarks..."
echo "[" >$LOGFILE

echo $rand

min=10
max=100
step=10
numtests=20

for i in $(eval echo "{$min..$max..$step}"); do
  echo "running for N = $i"
  echo {\"n\": $i, \"t\":[ >>$LOGFILE
  for j in $(eval echo "{1..$numtests}"); do
    python3 $SCRIPTDIR/gerador.py $i >$TESTFILE
    # date +%s%N returns the number of seconds since the epoch + current nanoseconds.
    ts=$(date +%s%N)
    result=$($1 $TESTFILE)
    elapsed=$((($(date +%s%N) - $ts) / 1000)) # time in microseconds
    if (($j != $numtests)); then
      echo "$elapsed," >>$LOGFILE
    else
      echo "$elapsed" >>$LOGFILE
    fi
  done
  rm $TESTFILE
  if (($i != $max)); then
    echo "]}," >>$LOGFILE
  else
    echo "]}" >>$LOGFILE
  fi

done
echo "]" >>$LOGFILE
echo "results generated at $LOGFILE"
