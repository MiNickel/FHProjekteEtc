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
@Path("kommentar")
public class Kommentar implements Serializable{
    
    String text;
    long article_id;
    
    public Kommentar(String text, long article_id){
        this.article_id = article_id;
        this.text = text;
    }
}
