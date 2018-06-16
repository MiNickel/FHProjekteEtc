/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package test;

import java.io.Serializable;
import javax.ws.rs.Path;

/**
 *
 * @author Jan Augstein
 */
@Path("aufgabe")
public class Aufgabe extends Artikel implements Serializable {

    private String Fach;
    
    public Aufgabe(int id, String Inhalt, String Titel, String Titelfarbe, String Startdatum, String Enddatum, String Fach){
        super(id, Inhalt, Titel, Titelfarbe, Startdatum, Enddatum);
        this.Fach = Fach;
    }
}
