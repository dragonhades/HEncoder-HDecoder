#!/bin/bash
in1=$(mktemp)
in2=$(mktemp)
out=$(mktemp)
file=$(mktemp)
echo pwd >> ${in1}
echo pwd >> ${in1}
echo pwd > ${in2}
cat ${in1} | ./HEncode $1 > ${out} 2> /dev/null
cat ${in2}| ./HDecode ${out} > ${file} 2> /dev/null
diff $1 ${file} > /dev/null
if [ $? -eq 1 ]; then 
  echo "Test fail!" >&2
  rm ${in1} ${in2} ${out} ${file}
  exit 1
else 
  echo "Test passed!" >&2
  rm ${in1} ${in2} ${out} ${file}
fi
