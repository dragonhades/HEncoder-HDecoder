#!/bin/bash
in1=$(mktemp)
in2=$(mktemp)
out=$(mktemp)
file=$(mktemp)
echo pwd >> ${in1}
echo pwd >> ${in1}
echo pwd > ${in2}
cat ${in1} | ./HEncode $1 > ${out}
cat ${in2}| ./HDecode ${out} > ${file}
diff $1 ${file}
rm ${in1} ${in2} ${out} ${file}
