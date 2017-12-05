package chat;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface ClientProxyIF extends Remote {
	public void receiveMessage (String message) throws RemoteException;
	
}
