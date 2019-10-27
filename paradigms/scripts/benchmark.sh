#!/bin/bash

if [ "$#" -ne 2 ]; then
  echo "usage: bash benchmark.sh [executable] [algorithm]"
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
LOGFILE="$TESTDIR/log_$2.json"

mkdir -p $TESTDIR

echo "runnig benchmarks..."
echo "[" >$LOGFILE

[[ $2 = "pd" ]] && min=100 || min=1000
[[ $2 = "pd" ]] && max=1000 || max=50000
[[ $2 = "pd" ]] && step=100 || step=1000
[[ $2 = "pd" ]] && numtests=10 || numtests=15
[[ $2 = "pd" ]] && times=3 || times=1

for i in $(eval echo "{$min..$max..$step}"); do
  for k in $(eval echo "{1..$times}") ; do
  echo {\"n\": $i, \"m\": $((100*(i / k))), \"t\":[ >>$LOGFILE
  echo "running for M = $i and N = $((100*(i / k)))"
    for j in $(eval echo "{1..$numtests}"); do
      
      python3 $SCRIPTDIR/gerador.py $i $((100*(i / k))) >$TESTFILE
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
    if [[($i == $max && $k == $times)]]; then
      echo "]}" >>$LOGFILE
    else
      echo "]}," >>$LOGFILE
    fi
  done
done
echo "]" >>$LOGFILE
echo "results generated at $LOGFILE"
