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

@Path("comment")
public class getKommentar implements Serializable {
    @GET
    @Produces(MediaType.APPLICATION_JSON)
    public Response getComment(@QueryParam("id") int id){
        Kommentar[] CommentList = new Kommentar[2];
        CommentList[0] = new Kommentar("Text1", 0);
        CommentList[1] = new Kommentar("Text2", 1);
        return Response.ok(CommentList[id]).build();
    }
}
