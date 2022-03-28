#!/bin/bash

PROG="./a.out"

for IN_FILE in sample/CZE/*_in.txt;
do
  OUT_FILE=`echo -n $IN_FILE | sed -e 's/in/out/g'`
  $PROG < "$IN_FILE" > tmp_out.txt
  if ! diff $OUT_FILE tmp_out.txt;
  then
    echo "Aborted test: $IN_FILE";
  else
    echo "Correct test $IN_FILE";
  fi
done

rm tmp_out.txt
