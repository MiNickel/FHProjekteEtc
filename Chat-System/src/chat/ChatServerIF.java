package chat;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface ChatServerIF extends Remote {
	public void subscribeUser (ClientProxyIF handle) throws RemoteException;
	
	public boolean unsubscribeUser (ClientProxyIF handle) throws RemoteException;
	
	public void broadcast(String message) throws RemoteException;
	
}
