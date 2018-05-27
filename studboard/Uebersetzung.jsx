function NewsUebersetzung() {
    var newsDE = ["Titel", "Autor", "Formular", "Startseite", "News", "Projekte", "Aufgaben", "Neuen Artikel anlegen"];
    var newsEN = ["title", "author", "form", "homepage", "news", "projects", "tasks", "new article"];
    var titel =" Titel";
    var autor, formular, startseite, news, projekte, aufgaben, neuerArtikel;
    if (navigator.language.indexOf("en")>-1){
        titel = newsEN[0];
        autor = newsEN[1];
        formular = newsEN[2];
        startseite = newsEN[3];
        news = newsEN[4];
        projekte = newsEN[5];
        aufgaben = newsEN[6];
        neuerArtikel = newsEN[7];
    }
    /*console.log(titel);
    document.getElementById("titel").innerHTML = titel;
    titelOut.innerHTML = titel;
    var autorOut = document.getElementById('autor');
    autorOut.innerHTML = autor;
    var formularOut = document.getElementById('formular');
    formularOut.innerHTML = formular;
    var startseiteOut = document.getElementById('startseite');
    startseiteOut.innerHTML = startseite;
    var newsOut = document.getElementById('news');
    newsOut.innerHTML = news;
    var projekteOut = document.getElementById('projekte');
    projekteOut.innerHTML = projekte;
    var aufgabenOut = document.getElementById('aufgaben');
    aufgabenOut.innerHTML = aufgaben;
    var neuerArtikelOut = document.getElementById('neuerArtikel');
    neuerArtikelOut.innerHTML = neuerArtikel;
    */
    console.log("Deutsch: Nachrichten, Englisch: News");
}
function ProjektUebersetzung() {
    console.log("Deutsch: Projekt, Englisch: Project");
}
function AufgabeUebersetzung() {
    console.log("Deutsch: Aufgabe, Englisch: Task");
}
function ArtikelAnlegenUebersetzung() {
    console.log("Deutsch: Startdatum, Englisch: start date\n\
Deutsch: Enddatum, Englisch: end date\n\
Deutsch: Artikeltext, Englisch: article text\n\
Deutsch: Artikelart, Englisch article type");
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