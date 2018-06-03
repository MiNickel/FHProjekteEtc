function StartUebersetzung() {
    var newsDE = ["Titel : ", "Autor : ", "Formular", "Startseite", "News", "Projekte", "Aufgaben", "Neuen Artikel anlegen"];
    var newsEN = ["Title : ", "Author : ", "form", "homepage", "news", "projects", "tasks", "new article"];
    var titel, autor, formular, startseite, news, projekte, aufgaben, neuerArtikel;
    if (navigator.language.indexOf("en")>-1){
        titel = newsEN[0];
        autor = newsEN[1];
        formular = newsEN[2];
        startseite = newsEN[3];
        news = newsEN[4];
        projekte = newsEN[5];
        aufgaben = newsEN[6];
        neuerArtikel = newsEN[7];
    } else if (navigator.language.indexOf("de")>-1){
        titel = newsDE[0];
        autor = newsDE[1];
        formular = newsDE[2];
        startseite = newsDE[3];
        news = newsDE[4];
        projekte = newsDE[5];
        aufgaben = newsDE[6];
        neuerArtikel = newsDE[7];
    }
 
    document.getElementById("titel1").innerHTML = titel;
    document.getElementById('autor1').innerHTML = autor;
    document.getElementById("titel2").innerHTML = titel;
    document.getElementById('autor2').innerHTML = autor;
    document.getElementById("titel3").innerHTML = titel;
    document.getElementById('autor3').innerHTML = autor;
    document.getElementById('startseite').innerHTML = startseite;
    document.getElementById('news').innerHTML = news;
    document.getElementById('projekte').innerHTML = projekte;
    document.getElementById('aufgaben').innerHTML = aufgaben;
    document.getElementById('neuerArtikel').innerHTML = neuerArtikel;

}
function NewsUebersetzung() {
    var newsDE = ["Titel : ", "Autor : ", "Formular", "Startseite", "News", "Projekte", "Aufgaben", "Neuen Artikel anlegen"];
    var newsEN = ["Title : ", "Author : ", "form", "homepage", "news", "projects", "tasks", "new article"];
    var titel, autor, formular, startseite, news, projekte, aufgaben, neuerArtikel;
    if (navigator.language.indexOf("en")>-1){
        titel = newsEN[0];
        autor = newsEN[1];
        formular = newsEN[2];
        startseite = newsEN[3];
        news = newsEN[4];
        projekte = newsEN[5];
        aufgaben = newsEN[6];
        neuerArtikel = newsEN[7];
    } else if (navigator.language.indexOf("de")>-1){
        titel = newsDE[0];
        autor = newsDE[1];
        formular = newsDE[2];
        startseite = newsDE[3];
        news = newsDE[4];
        projekte = newsDE[5];
        aufgaben = newsDE[6];
        neuerArtikel = newsDE[7];
    }
    
    document.getElementById("titel").innerHTML = titel;
    document.getElementById('autor').innerHTML = autor;
    document.getElementById('formular').innerHTML = formular;
    document.getElementById('startseite').innerHTML = startseite;
    document.getElementById('news').innerHTML = news;
    document.getElementById('projekte').innerHTML = projekte;
    document.getElementById('aufgaben').innerHTML = aufgaben;
    document.getElementById('neuerArtikel').innerHTML = neuerArtikel;
}
function ProjektUebersetzung() {
    var newsDE = ["Titel : ", "Autor : ", "Formular", "Startseite", "News", "Projekte", "Aufgaben", "Neuen Artikel anlegen"];
    var newsEN = ["Title : ", "Author : ", "form", "homepage", "news", "projects", "tasks", "new article"];
    var titel, autor, formular, startseite, news, projekte, aufgaben, neuerArtikel;
    if (navigator.language.indexOf("en")>-1){
        titel = newsEN[0];
        autor = newsEN[1];
        formular = newsEN[2];
        startseite = newsEN[3];
        news = newsEN[4];
        projekte = newsEN[5];
        aufgaben = newsEN[6];
        neuerArtikel = newsEN[7];
    } else if (navigator.language.indexOf("de")>-1){
        titel = newsDE[0];
        autor = newsDE[1];
        formular = newsDE[2];
        startseite = newsDE[3];
        news = newsDE[4];
        projekte = newsDE[5];
        aufgaben = newsDE[6];
        neuerArtikel = newsDE[7];
    }
    
    document.getElementById("titel").innerHTML = titel;
    document.getElementById('autor').innerHTML = autor;
    document.getElementById('formular').innerHTML = formular;
    document.getElementById('startseite').innerHTML = startseite;
    document.getElementById('news').innerHTML = news;
    document.getElementById('projekte').innerHTML = projekte;
    document.getElementById('aufgaben').innerHTML = aufgaben;
    document.getElementById('neuerArtikel').innerHTML = neuerArtikel;
}
function AufgabeUebersetzung() {
    var newsDE = ["Titel : ", "Autor : ", "Formular", "Startseite", "News", "Projekte", "Aufgaben", "Neuen Artikel anlegen"];
    var newsEN = ["Title : ", "Author : ", "form", "homepage", "news", "projects", "tasks", "new article"];
    var titel, autor, formular, startseite, news, projekte, aufgaben, neuerArtikel;
    if (navigator.language.indexOf("en")>-1){
        titel = newsEN[0];
        autor = newsEN[1];
        formular = newsEN[2];
        startseite = newsEN[3];
        news = newsEN[4];
        projekte = newsEN[5];
        aufgaben = newsEN[6];
        neuerArtikel = newsEN[7];
    } else if (navigator.language.indexOf("de")>-1){
        titel = newsDE[0];
        autor = newsDE[1];
        formular = newsDE[2];
        startseite = newsDE[3];
        news = newsDE[4];
        projekte = newsDE[5];
        aufgaben = newsDE[6];
        neuerArtikel = newsDE[7];
    }
    
    document.getElementById("titel").innerHTML = titel;
    document.getElementById('autor').innerHTML = autor;
    document.getElementById('formular').innerHTML = formular;
    document.getElementById('startseite').innerHTML = startseite;
    document.getElementById('news').innerHTML = news;
    document.getElementById('projekte').innerHTML = projekte;
    document.getElementById('aufgaben').innerHTML = aufgaben;
    document.getElementById('neuerArtikel').innerHTML = neuerArtikel;
}
function ArtikelAnlegenUebersetzung() {
    var newsDE = ["Titel : ", "Autor : ", "Formular", "Startseite", "News", "Projekte", "Aufgaben", "Neuen Artikel anlegen", "Geben sie ihren Text ein"];
    var newsEN = ["Title : ", "Author : ", "form", "homepage", "news", "projects", "tasks", "new article", "Enter your text here"];
    var titel, autor, formular, startseite, news, projekte, aufgaben, neuerArtikel, kommentar;
    if (navigator.language.indexOf("en")>-1){
        titel = newsEN[0];
        autor = newsEN[1];
        formular = newsEN[2];
        startseite = newsEN[3];
        news = newsEN[4];
        projekte = newsEN[5];
        aufgaben = newsEN[6];
        neuerArtikel = newsEN[7];
        kommentar = newsEN[8];
    } else if (navigator.language.indexOf("de")>-1){
        titel = newsDE[0];
        autor = newsDE[1];
        formular = newsDE[2];
        startseite = newsDE[3];
        news = newsDE[4];
        projekte = newsDE[5];
        aufgaben = newsDE[6];
        neuerArtikel = newsDE[7];
        kommentar = newsDE[8];
    }
    
    document.getElementById('startseite').innerHTML = startseite;
    document.getElementById('news').innerHTML = news;
    document.getElementById('projekte').innerHTML = projekte;
    document.getElementById('aufgaben').innerHTML = aufgaben;
    document.getElementById('neuerArtikel').innerHTML = neuerArtikel;
    document.getElementById('Kommentar').innerHTML = kommentar;
}

function WillkommenWindow() {
    var text = "";
    if (navigator.language.indexOf("en")>-1){
        text = "Welcome to Studboard"
    } else if (navigator.language.indexOf("de")>-1){
        text = "Willkommen zu Studboard"
    } 
    var fenster1 = window.open("", "popup1", "width=200,height=100");
    fenster1.document.write(text);
    fenster1.setTimeout("close()", 5000);
}

console.log("Deutsch: Titel, Englisch: Title\n\
Deutsch: Autor, Englisch: Author\n\
Deutsch: Formular, Englisch: Form\n\
Deutsch: sehr gut, Englisch: very good\n\
Deutsch: ungenuegend, Englisch: insufficient\n\
Deutsch: Datei auswaehlen, Englisch: Choose File\n\
Deutsch: Einsenden, Englisch: Submit\n\
Deutsch: Startseite, Englisch: Homepage");