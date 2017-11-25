package chat;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface ChatServerIF extends Remote {
	public void subscribeUser (ClientProxyIF handle) throws RemoteException;
	
	public void broadcastMessage(String message) throws RemoteException;
}
