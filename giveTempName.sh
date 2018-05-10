#!/bin/bash

# Macht, dass Leerzeichen mit gelesen werden und dei Zeilen nicht mehr gesplitet sind
IFS=$'\n'

FILEDIR="$HOME/.trashBin/.dir"
SEARCHEDFILE=$1

for line in $(cat $FILEDIR)
do
if [[ $line = *"$SEARCHEDFILE"* ]]; then
	# %% entfernt längsten möglichen String von Rechts(hinten) bis zum !
	TEMPNAME=${line%%!*}
	echo $TEMPNAME
fi
done
