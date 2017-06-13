#!/usr/bin/env bash

make

./gear_params -m S -i test_files/spur_input.txt > spur_output.txt
./gear_params -m R -i test_files/rack_input.txt > rack_output.txt
./gear_params -m U -i test_files/metric_input.txt > metric_output.txt

make clean

num_spur=$(wc -l test_files/spur_expected.txt | sed 's/^\([0-9]*\)\(.*\)$/\1/g')
for i in $(seq 1 1 $num_spur)
do
    line_check=$(head -n $i test_files/spur_expected.txt | tail -n 1)
    spur_check=$(grep -c $line_check spur_output.txt)
    if (( spur_check <1 ))
    then
	echo "Test failed spur_output.txt"
	exit 1
    fi
done
    
num_rack=$(wc -l test_files/rack_expected.txt | sed 's/^\([0-9]*\)\(.*\)$/\1/g')
for i in $(seq 1 1 $num_rack)
do
    line_check=$(head -n $i test_files/rack_expected.txt | tail -n 1)
    rack_check=$(grep -c $line_check rack_output.txt)
    if (( rack_check <1 ))
    then
	echo "Test failed rack_output.txt"
	exit 1
    fi
done

num_metric=$(wc -l test_files/metric_expected.txt | sed 's/^\([0-9]*\)\(.*\)$/\1/g')
for i in $(seq 1 1 $num_metric)
do
    line_check=$(head -n $i test_files/metric_expected.txt | tail -n 1)
    metric_check=$(grep -c $line_check metric_output.txt)
    if (( metric_check <1 ))
    then
	echo "Test failed metric_output.txt"
	exit 1
    fi
done

rm spur_output.txt rack_output.txt metric_output.txt

echo "Test passed"
exit 0
    
   
