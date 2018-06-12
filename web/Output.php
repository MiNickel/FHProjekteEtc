<?php

if (isset($_POST['Kommentar'])) {
    echo htmlentities($_POST['Kommentar']);
	echo "\n<br/>\n<br/>";
}
if(!empty($_POST['Bewertung'])) {
	$Bewertung=$_POST['Bewertung'];
	echo "Bewertung: " .$Bewertung;
	echo "\n<br/>\n<br/>";
}
if(!empty($_POST['Artikelart'])) {
	$Artikelart=$_POST['Artikelart'];
	echo "Artikelart: " .$Artikelart;
	echo "\n<br/>\n<br/>";
}
if(!empty($_POST['Startdatum'])) {
	$Startdatum=$_POST['Startdatum'];
	echo "Startdatum: " .$Startdatum;
	echo "\n<br/>\n<br/>";
}
if(!empty($_POST['Enddatum'])) {
	$Enddatum=$_POST['Enddatum'];
	echo "Enddatum: " .$Enddatum;
	echo "\n<br/>\n<br/>";
}
if(!empty($_POST['Titelfarbe'])) {
	$Titelfarbe=$_POST['Titelfarbe'];
	echo "Titelfarbe: " .$Titelfarbe;
	echo "\n<br/>\n<br/>";
}
echo "<pre>\r\n";
    echo htmlspecialchars(print_r($_FILES,1));
    echo "</pre>\r\n";


?>