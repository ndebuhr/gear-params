#!/usr/bin/env bash

module_char="$1"
input_file="$2"
output_file="$3"
expected_file="$4"

./gear_params -m "$module_char" -i "$input_file" >> "$output_file" 2>&1

num_exp_strings=$(wc -l "$input_file" | sed 's/^\([0-9]*\)\(.*\)$/\1/g')
for i in $(seq 1 1 $num_exp_strings)
do
    line_check=$(head -n $i "$expected_file" | tail -n 1)
    exp_check=$(grep -c $line_check "$output_file")
    if (( exp_check <1 ))
    then
	echo "Test failed $output_file"
	exit 1
    fi
done

rm "$output_file"

echo "Test passed"
exit 0
