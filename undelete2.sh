#!/bin/bash

# Leerzeichen werden mitgelesen
IFS=$'\n'

FILEDIR="$HOME/.trashBin/.dir"
TEMPFILEDIR="$HOME/.trashBin/.tempdir"
OLDNAME=$1

for line in $(cat $FILEDIR)
do 
if [[ $line = "$OLDNAME"* ]]; then
	# entfernt von links den kürzest möglichen String bis zum Leerzeichen
	ORIGIN=${line#* }

	# entfernt von links den größt möglichsten String bis /
	NEWNAME=${line##*/}

	# "Wiedeherstellen" der Datei + Überprüfung des Verzeichnis
	if [[ -d $ORIGIN ]]; then
		mv $OlDNAME $NEWNAME
		mv $NEWNAME $ORIGIN
		# löschen der Zeile in .dir
		grep -v $line $FILEDIR > $TEMPFILEDIR
		mv $TEMPFILEDIR $FILEDIR
	else
		echo "Das ursprüngliche Verzeichnis der Datei existiert nicht"
	fi
fi
done
