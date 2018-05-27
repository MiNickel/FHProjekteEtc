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


if (typeof(Storage) !== "undefined"){
    let visits = localStorage.getItem("visits");
    if (visits) {
        /*visitsNo = parseInt(visits);
        visitsNo++;
        localStorage.setItem("visits", visitsNo);*/
        artikel1 = localStorage.getItem(1);
        artikel2 = localStorage.getItem(2);
        artikel3 = localStorage.getItem(3);
        artikel4 = localStorage.getItem(4);
     
    } else {

        localStorage.setItem("visits", 1);
        localStorage.setItem(1, artikel1);
        localStorage.setItem(2, artikel2);
        localStorage.setItem(3, artikel3);
        localStorage.setItem(4, artikel4);
    }
    console.log("This is your " + localStorage.getItem("visits") + " visits");
    console.log(localStorage.getItem(1));
    console.log(artikel1);
    
} else {
    console.log("Sorry");
}
