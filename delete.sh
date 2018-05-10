#!/bin/bash

TRASHBIN="$HOME/.trashBin"
TIMESTAMP=$(date "+%y%m%d%H%M%S")
FILEPATH=$(pwd $1)
OLDNAME=$1
NEWNAME=$TIMESTAMP"_"$$".dat"

FILEDIR="$HOME/.trashBin/.dir"

echo "Verschiebe $1 nach $TRASHBIN"
# "Löschen" der Datei
mv $1 $NEWNAME
mv $NEWNAME $TRASHBIN

# Schreiben der Infos in .dir
echo $NEWNAME"! "$FILEPATH"/"$OLDNAME >> $FILEDIR

echo "Temporärer Name: $NEWNAME"
