package tcp;

import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class TCP {

    static byte[] datablock = "DATA;".getBytes();

   
    public static void main(String[] args) throws Exception {
        ServerSocket serverSocket = new ServerSocket(8999);
        Socket socket = serverSocket.accept();

        InputStream in = socket.getInputStream();
        OutputStream out = socket.getOutputStream();
        byte[] buffer = new byte[512];
 
        in.read(buffer);
    
        String init = new String(buffer);
        String[] parts = init.split(";");
        if (!parts[0].equals("INITX")) {
            out.write("ERROR;INITX erwartet".getBytes());
            out.flush();
            out.close();
            in.close();
            socket.close();
            System.err.println("Crash!");
            System.exit(1);
        }
        int size = Integer.parseInt(parts[1]);
        System.out.println(new String(buffer));
        File file = new File(parts[2].trim());
        file.exists(); 
        System.out.println(file.getAbsolutePath());

        FileInputStream fileIn = new FileInputStream(file);
        out.write("OK".getBytes());
        out.flush();
        buffer = new byte[size];
        in.read(buffer);
      
        int prefixsize = "DATA;".getBytes().length;
        do {
            buffer = new byte[size];
        
            fileIn.read(buffer, prefixsize, size - prefixsize);
            System.arraycopy(datablock, 0, buffer, 0, datablock.length);
            
            out.write(buffer);
            out.flush();

            buffer = new byte[size];
            in.read(buffer);
        } while (fileIn.available() > 0);
       
        out.write("FINISH".getBytes());
        out.flush();
        out.close();
        in.close();
        socket.close();
    }
}
