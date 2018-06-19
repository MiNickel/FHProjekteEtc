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

public class News extends Artikel {
    
    private String Kategorie;
    private String Quelle;
    
    public News(int id, String Inhalt, String Titel, String Titelfarbe, String Startdatum, String Enddatum, String Kategorie, String Quelle){
        super(id, Inhalt, Titel, Titelfarbe, Startdatum, Enddatum);
        this.Kategorie = Kategorie;
        this.Quelle = Quelle;
    }

    public String getKategorie() {
        return this.Kategorie;
    }

    public String getQuelle() {
        return this.Quelle;
    }
    
    
}
