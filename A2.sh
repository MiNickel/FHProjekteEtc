#!/bin/bash

dateHour=$(date +%H)

if [ $dateHour -ge 00 ] && [ $dateHour -le 12 ] 
then
	echo "Guten Morgen $USER"
elif [ $dateHour -ge 12 ] && [ $dateHour -le 17 ] 
then
	echo "Guten Tag $USER"
elif [ $dateHour -ge 17 ] && [ $dateHour -le 23 ]
then
	echo "Guten Abend $USER"
fi

