package tcp;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;

public class Client {

    public static void main(String[] args) throws IOException {
        Socket socket = new Socket("localhost", 8999);
        
     

        InputStream in = socket.getInputStream();
        OutputStream out = socket.getOutputStream();
       
        out.write("INITX;512;demo.txt".getBytes());
        out.flush();
      
        byte[] buffer = new byte[512];
        
        in.read(buffer);
        String nachricht = new String(buffer);
        String parts[] = nachricht.split(";");
        if (parts[0].equals("ERROR")) {
            System.err.println(parts[1]);
            in.close();
            out.close();
            socket.close();
            System.exit(1);
        }
       
        FileOutputStream outFile = new FileOutputStream("demo.txt");
        String prefix = "";
        do {
            out.write("GET".getBytes());
            out.flush();
            buffer = new byte[512];
            in.read(buffer);
            prefix = new String(buffer).split(";")[0];
            if(prefix.equals("DATA")){
                outFile.write(buffer, 5, 512 - 5);
                outFile.flush();
            }
        } while (prefix.equals("DATA"));

    }
}
