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
artikel2 = new Projekt("Inhalt", "KI-Projekt", "rot", "18.05.2018", "30.06.2018", "Prof Carsten Gips", 15);
artikel3 = new Aufgabe("Inhalt", "KI-Programmierung", "gruen", "18.05.2018", "25.06.2018", "Informatik");
artikel4 = new Aufgabe("Inhalt", "Probeklausur rechnen", "gruen", "14.05.2018", "18.05.2018", "Mathematik");

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
