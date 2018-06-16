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
@Path("projekt")
public class Projekt extends Artikel implements Serializable{
    
    private String Professor;
    private int AnzahlFreiePlätze;
    
    public Projekt(int id, String Inhalt, String Titel, String Titelfarbe, String Startdatum, String Enddatum, String Professor, int AnzahlFreiePlätze){
        super(id, Inhalt, Titel, Titelfarbe, Startdatum, Enddatum);
        this.Professor = Professor;
        this.AnzahlFreiePlätze = AnzahlFreiePlätze;
    }
    
}
