#!/bin/bash
suite=$(mktemp)
ls | egrep "*\.txt$" > $suite
stat=1
for input in $(cat $suite); do
  in1=$(mktemp)
  in2=$(mktemp)
  out=$(mktemp)
  file=$(mktemp)
  echo pwd >> ${in1}
  echo pwd >> ${in1}
  echo pwd > ${in2}
  cat ${in1} | ../HEncode ${input} > ${out} 2> /dev/null
  cat ${in2}| ../HDecode ${out} > ${file} 2> /dev/null
  diff ${input} ${file} > /dev/null
  if [ $? -eq 1 ]; then 
    echo "Test ${input} failed!"
    rm ${in1} ${in2} ${out} ${file}
    stat=0
  else 
    echo "Test passed!"
    rm ${in1} ${in2} ${out} ${file}
  fi
done
rm ${suite}
if [ ${stat} -eq 0 ]; then
  exit 1
fi
