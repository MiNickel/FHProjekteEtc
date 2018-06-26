#!/bin/bash

result=1
counter=0
filename=$0

while [ $# -ne 0 ]
do
	if [ "$counter" -ne "0" ]
	then
		result=$(( $result * $1))
	else
		firstParameter=$1
	fi

	shift
	counter=$[counter + 1]

done

result=$(($result / $firstParameter))
echo "Das Resultat ist: "$result
echo "Der Dateiname lautet: "${filename#*/}

