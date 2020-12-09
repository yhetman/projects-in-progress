#!/bin/bash

INPUT_FILE="input2.txt"
NUMBER_OF_PROCESSES=8

counter=0

while true;
do
	python start_process.py $INPUT_FILE &
	counter=$((counter + 1))
	if [[ $counter -eq $NUMBER_OF_PROCESSES ]] ; then
		break ;
	fi
done

