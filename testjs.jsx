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
artikel3 = new Aufgabe("Inhalt", "KI-Programmierung", "gr�n", "18.05.2018", "25.06.2018", "Informatik");
artikel3 = new Aufgabe("Inhalt", "Probeklausur rechnen", "gr�n", "14.05.2018", "18.05.2018", "Mathematik");

console.log(artikel1.Titel);


class JSONUmwandler{
    NewsToJSON(News){
       var jsonStr = JSON.stringify(News);
       return jsonStr;
    }
    
    ProjektToJSON(Projekt){
       var jsonStr = JSON.stringify({Projekt});
       return jsonStr;
    }
    
    AufgabeToJSON(Aufgabe){
       var jsonStr = JSON.stringify({Aufgabe});
       return jsonStr;
    }
    
  	JsonToObject(jsonStr){
      var jsonObj = JSON.parse(jsonStr);
      return jsonObj;
    }
    
}

JsonParser = new JSONUmwandler();
var json =JsonParser.NewsToJSON(artikel1);
console.log(json);
var Obj = JsonParser.JsonToObject(json);
console.log(Obj);