/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package REST;


/**
 *
 * @author Jan Augstein
 */

public class Aufgabe extends Artikel {

    private String Fach;
    
    public Aufgabe(int id, String Inhalt, String Titel, String Titelfarbe, String Startdatum, String Enddatum, String Fach){
        super(id, Inhalt, Titel, Titelfarbe, Startdatum, Enddatum);
        this.Fach = Fach;
    }

    public String getFach() {
        return this.Fach;
    }
    
    
}
