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
LOGFILE="$TESTDIR/log.txt"

mkdir -p $TESTDIR

for i in {10..90..10}; do
  echo "vertices: $i; instrucoes $i:" >>$LOGFILE
  python3 gerador.py $i $i >$TESTFILE
  for j in {1..20}; do
    # date +%s%N returns the number of seconds since the epoch + current nanoseconds.
    ts=$(date +%s%N)
    $1 $TESTFILE >/dev/null
    elapsed=$((($(date +%s%N) - $ts) / 1000)) # time in microseconds

    echo "$elapsed;" >>$LOGFILE
  done
  rm $TESTFILE
done
