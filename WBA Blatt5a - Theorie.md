#Webbasierte Anwendungen Blatt 5a

###Auf welche Arten kann ein JavaScript in eine HTML-Seite eingebunden werden?
1. External - Aus einer Datei, die im Header oder Body angegeben wird
				<script src="datei.js"></script>
2. Internal - Im Script-Tag, der im Header oder Body angegeben wird
				<script>
                	alert(script.funktion() );
                </script>

###Wann werden JavaScripte ausgeführt?
JavaScripte werden ausgeführt, sobald der Browser sie vollständig geladen hat
 -> Skripte können ausgeführt werden bevor das Dokument vollständig geladen ist
 -> Eventuell werden Funktionen zu früh ausgeführt
 -> Wenn ein Skript starte, könnten noch nicht alle Abhängigkeiten geladen sein