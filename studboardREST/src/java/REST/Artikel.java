/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package REST;

import javax.xml.bind.annotation.XmlRootElement;
/**
 *
 * @author Jan Augstein
 */
@XmlRootElement
public class Artikel {
    
   int id;
   String Inhalt;
   String Titel;
   String Titelfarbe;
   String Startdatum;
   String Enddatum;
    
    public Artikel(int id, String Inhalt, String Titel, String Titelfarbe, String Startdatum, String Enddatum) {
        this.id = id;
        this.Inhalt = Inhalt;
        this.Titel = Titel;
        this.Titelfarbe = Titelfarbe;
        this.Startdatum = Startdatum;
        this.Enddatum = Enddatum;
    }

    public int getId() {
        return this.id;
    }

    public String getInhalt() {
        return this.Inhalt;
    }

    public String getTitel() {
        return this.Titel;
    }

    public String getTitelfarbe() {
        return this.Titelfarbe;
    }

    public String getStartdatum() {
        return this.Startdatum;
    }

    public String getEnddatum() {
        return this.Enddatum;
    }
    
    
    
}
