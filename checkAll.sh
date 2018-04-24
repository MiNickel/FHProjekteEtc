#!/bin/bash

checkFile() {
echo "Überprüft ob eine Datei oder ein Verzeichnis existiert."
echo "Prüft..."
if [ -a $1 ]
 then
  echo "$1 existiert."
else
  echo "$1 existiert nicht."
fi
echo
}
checkRegularFile() {
echo "Überprüft ob es sich um eine reguläre Datei oder ein reguläres Verzeichnis handelt."
echo "Prüft..."

if [ -f $1 ]
 then
  echo "$1 ist regulär"
else
  echo "$1 ist nicht regulär"
fi
echo
}
checkSymbolicLink() {
echo "Überprüft ob es sich um einen symbolischen Link handelt."
echo "Prüft..."

if [ -h $1 ]
 then
  echo "$1 ist ein symbolischer Link."
else
  echo "$1 ist kein symbolischer Link."
fi
echo
}
checkOwner() {
echo "Überprüft ob der Aufrufer der Datei auch der Besitzer ist."
echo "Prüft..."

if [ -O $1 ]
 then
  echo "$UID ist der Besitzer der Datei"
else
  echo "$UID ist nicht der Besitzer der Datei"
fi
echo
}
retrieveOwner() {
echo "Gibt den Besitzer der Datei/ des Verzeichnisses aus."
USER=$(stat -c '%u' $1)
echo "$USER ist der Besitzer der Datei"
echo
}
checkFile $1
checkRegularFile $1
checkSymbolicLink $1
checkOwner $1
retrieveOwner $1
echo "Prüfung vollendet."
