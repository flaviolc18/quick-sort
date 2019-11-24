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
INDIR="$BASEDIR/test/dataset2/in"

mkdir -p $TESTDIR

echo "runnig benchmarks..."
echo "[" >$LOGFILE

Ns=(4 6 8 9)
Rs=(2 3 4 3)
Cs=(2 2 2 3)
FILES=(441.txt  661.txt  881.txt  991.txt)

for j in {0..3}; do
  echo "running for N = ${Ns[j]} I = ${Rs[j]} J = ${Cs[j]}"
  echo {\"N\": ${Ns[j]}, \"I\":${Rs[j]}, \"J\":${Cs[j]}, \"t\":[ >>$LOGFILE
  
  for i in {1..30}; do
    ts=$(date +%s%N)
    result=$($1 < $INDIR/${FILES[j]})
    elapsed=$((($(date +%s%N) - $ts) / 1000))
    echo $result

    if (($i != 30)); then
      echo "$elapsed," >>$LOGFILE
    else
      echo "$elapsed" >>$LOGFILE
    fi
  done
  if (($j == 3)); then
    echo "]}" >>$LOGFILE
  else
    echo "]}," >>$LOGFILE
  fi
done

echo "]" >>$LOGFILE
echo "results generated at $LOGFILE"
