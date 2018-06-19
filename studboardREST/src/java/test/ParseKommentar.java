/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package REST;

import javax.ws.rs.Consumes;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.core.Response;

/**
 *
 * @author Micha2
 */

@Path("comment/parse")
public class ParseKommentar {
    @POST
    
    public Response commentParse(String json){
        System.out.println(json);
        return Response.status(Response.Status.OK).build();
    }
}
