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
public class Kommentar {
    
   
    String text;
    long article_id;
    
    public Kommentar(String text, long article_id){
        this.article_id = article_id;
        this.text = text;
    }

    public String getText() {
        return this.text;
    }

    public long getArticle_id() {
        return this.article_id;
    }
    
    
    
    
}
