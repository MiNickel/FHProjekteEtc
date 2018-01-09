package tcp;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;

/**
 *
 * @author Alexander
 */
public class Client {

    public static void main(String[] args) throws IOException {
        Socket socket = new Socket("localhost", 8999);
        
        // Ab hier ist die Verbindung aufgebaut

        InputStream in = socket.getInputStream();
        OutputStream out = socket.getOutputStream();
        //senden der init message
        out.write("INITX;512;demo.txt".getBytes());
        out.flush();
        //empfangen des ersten packetes
        byte[] buffer = new byte[512];
        // Hier söllte nun entweder ein OK oder ein ERROr kommen
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
        // anfangen von Datenholen
        FileOutputStream outFile = new FileOutputStream("demo2.txt");
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
