/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package test;


import java.io.Serializable;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.QueryParam;
/**
 *
 * @author Jan Augstein
 */
@Path("artikel")
public class Artikel implements Serializable{
    
    private int id;
    private String Inhalt;
    private String Titel;
    private String Titelfarbe;
    private String Startdatum;
    private String Enddatum;
    
    public Artikel(int id, String Inhalt, String Titel, String Titelfarbe, String Startdatum, String Enddatum) {
        this.id = id;
        this.Inhalt = Inhalt;
        this.Titel = Titel;
        this.Titelfarbe = Titelfarbe;
        this.Startdatum = Startdatum;
        this.Enddatum = Enddatum;
    }
    
    @GET
    @Path("get")
    public String get(@QueryParam("id") Integer id){
        Artikel neu = new Artikel(1, "Inhalt", "Erster", "blau", "16.06.2018", "16.06.2018");
        String text = "";
        if(id == neu.id){
           text = neu.Inhalt + neu.Titel + neu.Titelfarbe + neu.Startdatum + neu.Enddatum;
        }
        System.out.print(text);
        return text;
    }
    
}
