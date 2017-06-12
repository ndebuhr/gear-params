#!/usr/bin/env bash

# Generate input files
echo "driving.teeth 64" > spur_input.txt
echo "driving.speed 52" >> spur_input.txt
echo "driven.teeth ?" >> spur_input.txt
echo "driven.speed 100" >> spur_input.txt
echo "nVal ?" > rack_input.txt
echo "pVal 32" >> rack_input.txt
echo "sVal 100" >> rack_input.txt
echo "dia_pitch ?" > metric_input.txt
echo "met_module 0.564" >> metric_input.txt

# Expected output file strings
spur_expected_1="100.85"
spur_expected_2="33"
spur_expected_3="97.88"
spur_expected_4="34"
rack_expected_1="994.718384"
metric_expected_1="45.035461"

make

./gear_params -m S -i spur_input.txt > spur_output.txt
./gear_params -m R -i rack_input.txt > rack_output.txt
./gear_params -m U -i metric_input.txt > metric_output.txt

make clean

spur_check_1=$(grep -c $spur_expected_1 spur_output.txt)
spur_check_2=$(grep -c $spur_expected_2 spur_output.txt)
spur_check_3=$(grep -c $spur_expected_3 spur_output.txt)
spur_check_4=$(grep -c $spur_expected_4 spur_output.txt)
rack_check_1=$(grep -c $rack_expected_1 rack_output.txt)
metric_check_1=$(grep -c $metric_expected_1 metric_output.txt)

if (( $spur_check_1 != 1 )) || (( $spur_check_2 != 1 )) || (( $spur_check_3 != 1 )) || (( $spur_check_4 != 1 ));
then
    echo "Issue with spur_output.txt"
    exit 1
fi
if (( $rack_check_1 != 1 ));
then
    echo "Issue with rack_output.txt"
    exit 1
fi
if (( $metric_check_1 != 1 ));
then
    echo "Issue with metric_output.txt"
    exit 1
fi

rm spur_input.txt rack_input.txt metric_input.txt
rm spur_output.txt rack_output.txt metric_output.txt

echo "Test passed"
exit 0
    
   
