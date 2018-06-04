//import JSONParser from 'JSON_Umwandlung.jsx';

function ArtikelToJSON(Artikel) {
        var jsonStr = JSON.stringify(Artikel);
        return jsonStr;
}

function JsonToObject(jsonStr){
      var jsonObj = JSON.parse(jsonStr);
      if (jsonObj.Kategorie){
        var Obj = Object.assign(new News, jsonObj);
      } else if (jsonObj.Professor) {
       	var Obj = Object.assign(new Projekt, jsonObj); 
      } else {
       	var Obj = Object.assign(new Aufgabe, jsonObj); 
      }
      return Obj;
}

class Artikel {
    
    constructor(Inhalt, Titel, Titelfarbe, Startdatum, Enddatum){
        this.Inhalt = Inhalt;
        this.Titel = Titel;
        this.Titelfarbe = Titelfarbe;
        this.Startdatum = Startdatum;
        this.Enddatum = Enddatum;
    }
    
    get inhalt(){
        return this.Inhalt;
    }
}

class News extends Artikel{
    
    constructor(Inhalt, Titel, Titelfarbe, Startdatum, Enddatum, Kategorie, Quelle){
        super(Inhalt, Titel, Titelfarbe, Startdatum, Enddatum);
        this.Kategorie = Kategorie;
        this.Quelle = Quelle;
    }
    
}

class Projekt extends Artikel{
    
    constructor(Inhalt, Titel, Titelfarbe, Startdatum, Enddatum, Professor, AnzahlFreieArbeitsplaetze){
        super(Inhalt, Titel, Titelfarbe, Startdatum, Enddatum);
        this.Professor = Professor;
        this.AnzahlFreieArbeitsplaetze = AnzahlFreieArbeitsplaetze;
    }
    
}

class Aufgabe extends Artikel{
    
    constructor(Inhalt, Titel, Titelfarbe, Startdatum, Enddatum, Fach){
        super(Inhalt, Titel, Titelfarbe, Startdatum, Enddatum);
        this.Fach = Fach;
    }
    
}

artikel1 = new News("Inhalt", "Erste News", "blau", "30.05.2018", "30.05.2018", "Allerlei", "TestQuelle");
artikel2 = new Projekt("Inhalt2", "KI-Projekt", "rot", "18.05.2018", "30.06.2018", "Prof Carsten Gips", 15);
artikel3 = new Aufgabe("Inhalt", "KI-Programmierung", "gruen", "18.05.2018", "25.06.2018", "Informatik");
artikel4 = new Aufgabe("Inhalt", "Probeklausur rechnen", "gruen", "14.05.2018", "18.05.2018", "Mathematik");

var artikel = [artikel1, artikel2, artikel3, artikel4];
/*console.log(ArtikelToJSON(artikel1));
var str = ArtikelToJSON(artikel1); 
console.log(JsonToObject(str));*/

if (typeof(Storage) !== "undefined"){
    let visits = localStorage.getItem(1);
    if (visits) {
        console.log("Artikel werden aus dem localStorage geladen");
        artikel1 = JsonToObject(localStorage.getItem(1));
        artikel2 = JsonToObject(localStorage.getItem(2));
        artikel3 = JsonToObject(localStorage.getItem(3));
        artikel4 = JsonToObject(localStorage.getItem(4));
        console.log(artikel1);
        artikel = [artikel1, artikel2, artikel3, artikel4];
    } else {

        console.log("Artikel werden erstmals gespeichert");
        localStorage.setItem(1, ArtikelToJSON(artikel1));
        localStorage.setItem(2, ArtikelToJSON(artikel2));
        localStorage.setItem(3, ArtikelToJSON(artikel3));
        localStorage.setItem(4, ArtikelToJSON(artikel4));
    }
   /* console.log("This is your " + localStorage.getItem("visits") + " visits");
    console.log(localStorage.getItem(1));
    console.log(artikel1);*/
    
} else {
    console.log("Sorry. LocalStorage wird nicht unterstüzt");
}

function loadStorage(anzahl) {
    console.log(artikel2);
    for (i=0; i<anzahl; i++){
        let myNewArticle = document.createElement("div");
        myNewArticle.setAttribute("style", "width:500px;");
        if (artikel[i] instanceof News){
            myNewArticle.setAttribute("class", "News Artikel");
        } else if(artikel[i] instanceof Projekt){
            myNewArticle.setAttribute("class", "Projekt Artikel");
        } else {
            myNewArticle.setAttribute("class", "Aufgabe Artikel");
        }
        let newArticle = document.createElement("article");
        //myNewArticle.appendChild(newArticle);

        let newHeader = document.createElement("header");
        newArticle.appendChild(newHeader);
        let newTitel = document.createElement("strong");
        newTitel.setAttribute("id", "titel");
        newTitel.appendChild(document.createTextNode("Titel : "));
        let newTitel2 = document.createElement("strong");
        if (artikel[i] instanceof News){
            newTitel2.appendChild(document.createTextNode("News"));
        } else if(artikel[i] instanceof Projekt){
            newTitel2.appendChild(document.createTextNode("Projekte"));
        } else {
            newTitel2.appendChild(document.createTextNode("Aufgaben"));
        }
        
        let newBreak = document.createElement("br");
        let newAutor = document.createElement("strong");
        newAutor.appendChild(document.createTextNode("Autor : "));
        let newAutor2 = document.createElement("strong");
        newAutor2.appendChild(document.createTextNode("Max Mustermann2"));
        
        newHeader.appendChild(newTitel);
        newHeader.appendChild(newTitel2);
        newHeader.appendChild(newBreak);
        newHeader.appendChild(newAutor);
        newHeader.appendChild(newAutor2);

        let newText = document.createElement("p");
        newText.setAttribute("style", "white-space: nowrap; overflow:hidden; text-overflow: ellipsis;");
        let object = artikel[i];
        let newContent = object.inhalt;
        newText.appendChild(document.createTextNode(newContent));
        newArticle.appendChild(newText);

        let newLink = document.createElement("a");
        if (artikel[i] instanceof News){
            newLink.setAttribute("href", "News.html");
        } else if(artikel[i] instanceof Projekt){
            newLink.setAttribute("href", "Projekte.html");
        } else {
            newLink.setAttribute("href", "Aufgaben.html");
        }
        newLink.appendChild(document.createTextNode("mehr..."));
        newArticle.appendChild(newLink);

        myNewArticle.appendChild(newArticle);


        let firstArticle = document.querySelector("body div");
        firstArticle.parentNode.insertBefore(myNewArticle, firstArticle.nextSibling);
        
        
        
    }
    
    let myNewMenu = document.createElement("nav");
    myNewMenu.setAttribute("class", "rechts2");
    for (j=0; j<anzahl; j++){
        let newMenuLink = document.createElement("a");
        newMenuLink.appendChild(document.createTextNode(artikel[j].Titel));
        if (artikel[i] instanceof News){
            newMenuLink.setAttribute("href", "News.html");
        } else if(artikel[i] instanceof Projekt){
            newMenuLink.setAttribute("href", "Projekte.html");
        } else {
            newMenuLink.setAttribute("href", "Aufgaben.html");
        }
        myNewMenu.appendChild(newMenuLink);
    }
    
    let firstMenu = document.querySelector("nav");
    firstMenu.parentNode.insertBefore(myNewMenu, firstMenu.nextSibling);
}

function saveArticle(){
    console.log(document.getElementById("Kommentar").value);
    console.log(document.getElementById("newsButton").checked);
    console.log(document.getElementById("projektButton").checked);
    console.log(document.getElementById("aufgabenButton").checked);
    console.log(document.getElementById("startdatum").value);
    console.log(document.getElementById("enddatum").value);
    console.log(document.getElementById("titelfarbe").value);
    console.log(localStorage.getItem(5));
    if(document.getElementById("newsButton").checked){
        //artikel1 = new News("Inhalt", "Erste News", "blau", "30.05.2018", "30.05.2018", "Allerlei", "TestQuelle");
        let inhalt = document.getElementById("Kommentar").value;
        let titel = document.getElementById("titel").value;
        let farbe = document.getElementById("titelfarbe").value;
        let startdatum = document.getElementById("startdatum").value;
        let enddatum = document.getElementById("enddatum").value;
        let kategorie = document.getElementById("zusatz").value;
        let quelle = document.getElementById("zusatz2").value;
        let artikel = new News(inhalt, titel, farbe, startdatum, enddatum, kategorie, quelle);
        console.log(artikel);
        let storageLength = localStorage.length;
        localStorage.setItem(storageLength+1, ArtikelToJSON(artikel));
        
    }
}
