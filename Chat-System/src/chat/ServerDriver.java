package chat;

import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.RemoteException;

public class ServerDriver {

	public static void main(String[] args) throws RemoteException, MalformedURLException {
		Naming.rebind("ChatServer", new ChatServer());
		

	}

}
