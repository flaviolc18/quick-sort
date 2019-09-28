if [ "$#" -ne 1 ]; then
  echo "usage: bash benchmark.sh [executable]"
  exit 2
fi

if [ ! -x $1 ]; then
  echo "invalid executable $1"
  exit 2
fi

TESTDIR=test
TESTFILE="$TESTDIR/t.txt"
LOGFILE="$TESTDIR/log.json"

mkdir -p $TESTDIR

echo "runnig benchmarks..."
echo "[" >$LOGFILE

echo $rand

for i in {10..100..10}; do
  # a=$(shuf -i $(($i - 1))-$(($i * ($i - 1) / 2)) -n 1)
  a=$(($i * ($i - 1) / 2))
  echo "{v: $i, a: $a, i: $i, r:[" >>$LOGFILE
  python3 gerador.py $i $a $i >$TESTFILE
  for j in {1..50}; do
    # date +%s%N returns the number of seconds since the epoch + current nanoseconds.
    ts=$(date +%s%N)
    result=$($1 $TESTFILE)
    elapsed=$((($(date +%s%N) - $ts) / 1000)) # time in microseconds

    echo "$elapsed," >>$LOGFILE
  done
  rm $TESTFILE
  echo "]}," >>$LOGFILE
done
echo "]" >>$LOGFILE
echo "results generated at $LOGFILE"
