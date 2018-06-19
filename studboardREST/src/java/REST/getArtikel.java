/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package REST;


import java.io.Serializable;
import javax.ws.rs.*;
import javax.ws.rs.core.*;


/**
 *
 * @author Micha2
 */

@Path("artikel")
public class getArtikel implements Serializable {
    
    @GET
   // @Produces(MediaType.APPLICATION_JSON)
    public Response getArtikel(@QueryParam("id") int id){
        Artikel articleListe[] = new Artikel[1];
        articleListe[0] = new Artikel(0, "Inhalt", "Titel", "#000000", "2018-04-03", "2018-05-07");
        System.out.println(articleListe[0].id);
        return Response.ok(articleListe[id]).build();
    }
    
}
