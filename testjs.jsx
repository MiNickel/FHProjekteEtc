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
      if (jsonObj.Kategorie){
        var Obj = Object.assign(new News, jsonObj);
      } else if (jsonObj.Professor) {
       	var Obj = Object.assign(new Projekt, jsonObj); 
      } else {
       	var Obj = Object.assign(new Aufgabe, jsonObj); 
      }
      return Obj;
    }
    
}

JsonParser = new JSONUmwandler();
var json =JsonParser.NewsToJSON(artikel3);
console.log(json);
var Obj = JsonParser.JsonToObject(json);
console.log(Obj.Kategorie);
console.log(Obj.Professor);
console.log(Obj.Fach);
//var test = Object.assign(new News, Obj);
//console.log(test.Kategorie);