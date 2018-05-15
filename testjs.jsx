
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
    
    constructor(Inhalt, Titel, Titelfarbe, Startdatum, Enddatum, Professor, AnzahlFreieArbeitsplätze){
        super(Inhalt, Titel, Titelfarbe, Startdatum, Enddatum);
        this.Professor = Professor;
        this.AnzahlFreieArbeitsplätze = AnzahlFreieArbeitsplätze;
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
artikel3 = new Aufgabe("Inhalt", "KI-Programmierung", "grün", "18.05.2018", "25.06.2018", "Informatik");
artikel3 = new Aufgabe("Inhalt", "Probeklausur rechnen", "grün", "14.05.2018", "18.05.2018", "Mathematik");

console.log(artikel1.Titel);


class JSONUmwandler{
    NewsToJSON(News){
       var jsonStr = JSON.stringify({News});
       console.log(jsonStr);
    }
    
    ProjektToJSON(Projekt){
       var jsonStr = JSON.stringify({Projekt});
       console.log(JsonStr);
    }
    
    AufgabeToJSON(Aufgabe){
       var jsonStr = JSON.stringify({Aufgabe});
       console.log(jsonStr);
    }
    
  	JsonToObject(jsonStr){
      var jsonObj = JSON.parse(jsonStr);
      console.log(jsonObj);
    }
    
}

JsonParser = new JSONUmwandler();
JsonParser.NewsToJSON(artikel1);
JsonParser.JsonToObject('{"News":{"Inhalt":"Inhalt","Titel":"Erste News","Titelfarbe":"blau","Startdatum":"30.05.2018","Enddatum":"30.05.2018","Kategorie":"Allerlei","Quelle":"TestQuelle"}}');