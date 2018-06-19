/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package REST;

import java.io.Serializable;
import javax.ws.rs.Path;

/**
 *
 * @author Jan Augstein
 */

public class Projekt extends Artikel {
    
    private String Professor;
    private int AnzahlFreiePlätze;
    
    public Projekt(int id, String Inhalt, String Titel, String Titelfarbe, String Startdatum, String Enddatum, String Professor, int AnzahlFreiePlätze){
        super(id, Inhalt, Titel, Titelfarbe, Startdatum, Enddatum);
        this.Professor = Professor;
        this.AnzahlFreiePlätze = AnzahlFreiePlätze;
    }

    public String getProfessor() {
        return this.Professor;
    }

    public int getAnzahlFreiePlätze() {
        return this.AnzahlFreiePlätze;
    }
    
    
    
}
