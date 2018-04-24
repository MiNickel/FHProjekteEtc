#!/bin/bash

checkFile() {

echo "Überprüft ob eine Datei oder ein Verzeichnis existiert."
echo "Prüft..."
for file in "$@"
do
if [ -a $file ]
 then
  echo "$file existiert."
else
  echo "$file existiert nicht."
fi
done
echo
}
checkRegularFile() {
echo "Überprüft ob es sich um eine reguläre Datei oder ein reguläres Verzeichnis handelt."
echo "Prüft..."
for file in "$@"
do
if [ -f $file ]
 then
  echo "$file ist regulär"
else
  echo "$file ist nicht regulär"
fi
done
echo
}
checkSymbolicLink() {
echo "Überprüft ob es sich um einen symbolischen Link handelt."
echo "Prüft..."
for file in "$@"
do
if [ -h $file ]
 then
  echo "$file ist ein symbolischer Link."
else
  echo "$file ist kein symbolischer Link."
fi
done
echo
}
checkOwner() {
echo "Überprüft ob der Aufrufer der Datei auch der Besitzer ist."
echo "Prüft..."
for file in "$@"
do
if [ -O $file ]
 then
  echo "$UID ist der Besitzer der Datei $file"
else
  echo "$UID ist nicht der Besitzer der Datei $file"
fi
done
echo
}
retrieveOwner() {
echo "Gibt den Besitzer der Datei/ des Verzeichnisses aus."
for file in "$@"
do
USER=$(stat -c '%u' $file)
echo "$USER ist der Besitzer der Datei $file"
done
echo
}

checkFile "$@"
checkRegularFile "$@"
checkSymbolicLink "$@"
checkOwner "$@"
retrieveOwner "$@"

echo "Prüfung vollendet."
